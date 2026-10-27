import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file generated from your C++ program
df = pd.read_csv(r"cpp\Important\time_complexities.csv")

# --- Graph 1: O(1) to O(n log n) for n = 1 to 100 ---
plt.figure(figsize=(9, 5))
sub_quadratic = ["O(1)", "O(log n)", "O(sqrt(n))", "O(n)", "O(n log n)"]
for col in sub_quadratic:
  plt.plot(df["n"], df[col], marker="o", label=col)

plt.title("Graph 1: Sub-Quadratic & Linear Time Complexities")
plt.xlabel("Input Size (n)")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("graph1.png")
plt.show()

# --- Graph 2: O(n^2) and O(n^3) for n = 1 to 50 ---
plt.figure(figsize=(9, 5))
polynomial = ["O(n^2)", "O(n^3)"]
for col in polynomial:
  valid_df = df[df[col] != -1]  # filter out any guardrail limits if applicable
  plt.plot(valid_df["n"], valid_df[col], marker="s", label=col)

plt.title("Graph 2: Polynomial Time Complexities")
plt.xlabel("Input Size (n)")
plt.ylabel("Time (microseconds)")
plt.legend()
plt.grid(True)
plt.savefig("graph2.png")
plt.show()