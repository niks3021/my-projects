import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score


# --- STEP 1: LOAD THE DATASET ---
# Fetch the raw dataset and convert it into a Pandas DataFrame
data = fetch_california_housing(as_frame=True)
df = data.frame


# --- STEP 2: FEATURE ENGINEERING & CLEANING ---
# Create a new, more useful ratio feature (luxurious/open layout vs dense)
df["Bedrooms_Per_Room"] = df["AveBedrms"] / df["AveRooms"]

# Drop the redundant raw column so the model doesn't get confused
df = df.drop(columns=["AveBedrms"])


# --- STEP 3: SEPARATE FEATURES (X) AND TARGET (y) ---
# X = Everything we use to make a prediction
# y = The value we want to predict (Median House Value)
X = df.drop(columns=["MedHouseVal"])
y = df["MedHouseVal"]


# --- STEP 4: SPLIT INTO TRAIN & TEST SETS ---
# Reserve 80% for training the model and 20% for testing unseen data.
# random_state=42 ensures you get the exact same split every time you run it.
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)


# --- STEP 5: FEATURE SCALING (STANDARDIZATION) ---
# Scale features so large numbers (like Population) don't overpower small ones (like MedInc).
scaler = StandardScaler()

# FIT and TRANSFORM on training data (learn mean/std from train set)
X_train_scaled = scaler.fit_transform(X_train)

# ONLY TRANSFORM on test data (prevents data leakage from test set)
X_test_scaled = scaler.transform(X_test)


# --- STEP 6: TRAIN THE MODEL ---
# Initialize the Linear Regression model and fit it onto the scaled training data
model = LinearRegression()
model.fit(X_train_scaled, y_train)


# --- STEP 7: MAKE PREDICTIONS & EVALUATE ---
# Feed unseen test data into the trained model
y_pred = model.predict(X_test_scaled)

# Evaluate metrics
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print("--- MODEL RESULTS ---")
print(f"Mean Squared Error (MSE): {mse:.4f}")
print(f"R² Score (Variance Explained): {r2:.4f}")


# 1. Grab a random row index from the test set
random_idx = y_test.sample(1, random_state=7).index[0]

# 2. Get the actual ground-truth price (scaled back to dollars)
actual_price = y_test.loc[random_idx] * 100000

# 3. Get the pre-scaled feature row for that index & predict
single_sample_scaled = X_test_scaled[y_test.index.get_loc(random_idx)].reshape(1, -1)
predicted_price = model.predict(single_sample_scaled)[0] * 100000

# 4. Calculate absolute error
diff = abs(actual_price - predicted_price)

print("\n--- INDIVIDUAL TEST SAMPLE CHECK ---")
print(f"Actual Price:    ${actual_price:,.2f}")
print(f"Predicted Price: ${predicted_price:,.2f}")
print(f"Difference:      ${diff:,.2f}")