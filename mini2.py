# !pip install shap     # uncomment in Colab if shap is missing
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import shap as shap
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPRegressor
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

#---
# 1. LOAD DATASET
#---
# Chemical manufacturing process dataset (yield is continuous so regression works)
df = pd.read_csv("chem_process.csv")

print(df.shape)
print(df.isnull().sum().sum(), "missing values")

# drop only the rows with no yield (dropping every row with a gap would delete too much data)
df = df.dropna(subset=['Yield'])

#---
# 2. DEFINE FEATURES AND TARGET
#---
# Using all columns except 'Yield' as features, and 'Yield' as target
X = df.drop(columns=['Yield'])
y = df['Yield']

# Train-test split: 80% training, 20% testing
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# fill missing values with the median of the TRAINING data only (so test data doesnt leak in)
train_medians = X_train.median()
X_train = X_train.fillna(train_medians)
X_test = X_test.fillna(train_medians)

#---
# 3. FEATURE SCALING
#---
# Standardize features so larger numerical ranges don't overpower the network
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

#---
# 4. NEURAL NETWORK REGRESSION MODEL
#---
# MLPRegressor = multi layer perceptron regressor from sklearn
mlp_model = MLPRegressor(
    hidden_layer_sizes=(64, 32), # two hidden layers with 64 and 32 neurons
    activation='relu', # makes negative numbers zero while keeps positive same ReLU = Rectified linear unit
    solver='adam', # optimiser adam = adaptive moment estimation
    max_iter=1000,  # making max iterations (1000 so it has enough time to converge)
    random_state=42 # Seed to make random numbers
)

mlp_model.fit(X_train_scaled, y_train) # training the model using fit

#---
# 5. EVALUATION AND METRICS
#---
y_pred = mlp_model.predict(X_test_scaled) # making predictions

mae = mean_absolute_error(y_test, y_pred) # find mean absolute error mae = sum of error (absolute) divided by total entries
rmse = np.sqrt(mean_squared_error(y_test, y_pred)) # root mean squared error = square root of the average of (actual - predicted)^2
r2 = r2_score(y_test, y_pred) # find r squared = 1 - (sum of (actual - predicted)^2 divided by sum of (actual - mean)^2)

print(f"Mean Absolute Error (MAE): {mae:.4f}")
print(f"Root Mean Squared Error (RMSE): {rmse:.4f}")
print(f"R-squared (R2) Score: {r2:.4f}")

# baseline: simple linear regression to compare against the neural network
lr = LinearRegression().fit(X_train_scaled, y_train)
print(f"Linear regression baseline R2: {r2_score(y_test, lr.predict(X_test_scaled)):.4f}")

#---
# 6. PLOTS
#---
# RESIDUAL PLOT
# Checks if errors (Actual - Predicted) scattering randomly (else they overlap on top).
# red line = no error line
residuals = y_test - y_pred

plt.figure(figsize=(8, 5)) # canvas 8 by 5 in
plt.scatter(y_pred, residuals, color='blue', alpha=0.6, edgecolor='k') # scatter blue dots 0.6 transparency + add black border
plt.axhline(y=0, color='red', linestyle='--', linewidth=2) # dotted -- line red colured for zero error
plt.title('Residual Plot for Chemical Yield Prediction') # title
plt.xlabel('Predicted Reaction Yield (%)') # label x axis
plt.ylabel('Residuals (Actual - Predicted)') # label y axis
plt.grid(True, linestyle=':', alpha=0.7) # make grid dotted and 0.7 alpha (= transparency)
plt.savefig('residual_plot.png', dpi=300, bbox_inches='tight') # save the result with dots per inch is 300 and make sure no label is ignored
plt.show() # show the plot

# ACTUAL VS PREDICTED
# dots on the red dashed line = perfect prediction
plt.figure(figsize=(6, 5))
plt.scatter(y_test, y_pred, alpha=0.6, edgecolor='k')
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'r--') # perfect prediction line
plt.xlabel('Actual Yield')
plt.ylabel('Predicted Yield')
plt.title('Actual vs Predicted Yield')
plt.savefig('actual_vs_predicted.png', dpi=300, bbox_inches='tight')
plt.show()

# LOSS CURVE
# shows how the training error went down while the network was learning
plt.figure(figsize=(6, 4))
plt.plot(mlp_model.loss_curve_)
plt.xlabel('Iteration')
plt.ylabel('Loss')
plt.title('Training Loss Curve')
plt.savefig('loss_curve.png', dpi=300, bbox_inches='tight')
plt.show()

#---
# 7. EXPLAINABLE AI (SHAP)
#---
# only 50 background rows and 30 test rows because KernelExplainer is slow with 57 features
explainer = shap.KernelExplainer(mlp_model.predict, X_train_scaled[:50])
shap_values = explainer.shap_values(X_test_scaled[:30])

# max_display=10 = show only the 10 most important features
shap.summary_plot(shap_values, X_test.iloc[:30], feature_names=X.columns, max_display=10)