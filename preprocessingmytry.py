import pandas as pd
from sklearn.datasets import fetch_california_housing
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

data = fetch_california_housing(as_frame=True)
df = data.frame
df["Bedroom-Room Ratio"] = df["AveBedrms"] / df["AveRooms"]
df = df.drop(columns =["AveBedrms"])
X = df.drop(columns = ["MedHouseVal"])
Y = df["MedHouseVal"]
X_train, X_test, y_train, y_test = train_test_split(
    X, Y, test_size=0.25, random_state=40
)
scaler = StandardScaler()

X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled  = scaler.transform(X_test)

model = LinearRegression()
model.fit(X_train_scaled, y_train)
Y_prediction = model.predict(X_test_scaled)

mse = mean_squared_error(y_test, Y_prediction)
r2 = r2_score(y_test, Y_prediction)

print("--- MODEL RESULTS ---")
print(f"Mean Squared Error (MSE): {mse:.4f}")
print(f"R² Score (Variance Explained): {r2:.4f}")

random_idx = y_test.sample(1, random_state=10).index[0]

actual_price = y_test.loc[random_idx] * 100000

single_sample_scaled = X_test_scaled[y_test.index.get_loc(random_idx)].reshape(1, -1)
predicted_price = model.predict(single_sample_scaled)[0] * 100000

diff = abs(actual_price - predicted_price)

print("\n--- INDIVIDUAL TEST SAMPLE CHECK ---")
print(f"Actual Price:    ${actual_price:,.2f}")
print(f"Predicted Price: ${predicted_price:,.2f}")
print(f"Difference:      ${diff:,.2f}")