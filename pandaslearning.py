import pandas as pd  

df = pd.read_csv(r".ms-ad\Data.csv",index_col="Name")

# pokemon = input("Which pokemon you want to search: ").strip().title()
# try:
#     print(df.loc[pokemon])
# except KeyError:
#     print(f"{pokemon} not found")
# print(df[(df["Type1"] == "Water") | (df["Type2"] == "Water")])
group = df.groupby(["Type1"])
print(group.size())
# print(group["Weight"].max())
heaviest_per_type = df.sort_values(by="Weight", ascending=False).groupby("Type1").first()
print(heaviest_per_type[["Weight"]])