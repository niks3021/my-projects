import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
# lets load the dataset
url = "https://raw.githubusercontent.com/shrikant-temburwar/Loan-Prediction-Dataset/master/train.csv"
df = pd.read_csv(url)

# printing first 5 elements
print(df.head())

# shape of dataset
print(df.shape)

# ---------
# PRE PROCESSING 
# ---------

# lets drop the loan id since its redundant
df.drop(columns=['Loan_ID'],inplace= True)

# Handle Missing Values
categorical_cols = ['Gender', 'Married', 'Dependents', 'Self_Employed', 'Credit_History', 'Loan_Amount_Term']
for col in categorical_cols:
    df[col] = df[col].fillna(df[col].mode()[0]) #filing with most frequent value

# lets fill the missing loan values with median of all loan values
df['LoanAmount'] = df['LoanAmount'].fillna(df['LoanAmount'].median())

# combining income into one 
df['TotalIncome'] = df['ApplicantIncome'] + df['CoapplicantIncome']

# since incomes and loan amounts are very large lets take log of them 
# e.g 10000 and 100000 are 90000 apart but their log is about 2.3 apart
df['TotalIncome_Log'] = np.log(df['TotalIncome'])
df['LoanAmount_Log'] = np.log(df['LoanAmount'])

# ok now drop untransformed columns now
df.drop(columns=['ApplicantIncome', 'CoapplicantIncome', 'TotalIncome', 'LoanAmount'], inplace=True)

# mapping accepted as 1 and rejected as 0
df['Loan_Status'] = df['Loan_Status'].map({'Y': 1, 'N': 0})

#dependents have 0,1,2,3 or 3+ lets just make them 4
df['Dependents'] = df['Dependents'].replace({'3+': 4}).astype(int)

# now almost all columns are numerical lets encode the remaining onesmainly the urban,rural,semiurban left
cleaned_df = pd.get_dummies(df, drop_first=True) # dropping case for rural so 0,0 = rural 1,0 = semi and 0,1 = urban

# lets normalise all the numbers from 0 to 1 so both 0,1 for gender and 0,100000 for income affect closely (ignore bias and weights)
scaler = MinMaxScaler() #from sklearn

# scaling specifically big amount columns
scale_cols = ['TotalIncome_Log', 'LoanAmount_Log', 'Loan_Amount_Term', 'Dependents']
cleaned_df[scale_cols] = scaler.fit_transform(cleaned_df[scale_cols])

# lets see the data set now
print("After Preprocessing")
print(cleaned_df.head())

#final shape
print(cleaned_df.shape)
# checking number of nulls/empty feilds
print("\nMissing values remaining:", cleaned_df.isnull().sum().sum())

print(cleaned_df['Loan_Status'])

# preparing train and test splits
Y = cleaned_df['Loan_Status']
X = cleaned_df.drop(columns=['Loan_Status'])
# now split
X_train,X_test,Y_train,Y_test = train_test_split(X,Y,test_size = 0.20,random_state = 42,stratify = Y)
# test size 0.2 means 20% test and rest is train 
# startify y maintains the ratio of 0,1 in the sprits so if 69% yes and 31% no it stays same in both test and train
# random state is the seed for random shuffling of data

print("Total records:",X.shape[0])
print("Train records:",X_train.shape[0])
print("Test Records:",X_test.shape[0])

# testing how many features
print("Features:")
print(X_train.columns.tolist())
# -------
# LOGISTIC REGRESSION
# -------

# initialise the model
model = LogisticRegression(max_iter= 1000, class_weight='balanced')
# max_iter means 1000 max iterations so we have enough and balanced to keep the ration of approve and reject

# train using fit()
model.fit(X_train,Y_train)

#predictions
Y_train_pred = model.predict(X_train)
Y_test_pred = model.predict(X_test)

#checking the predictions
train_acc = accuracy_score(Y_train, Y_train_pred)
test_acc = accuracy_score(Y_test, Y_test_pred)

print(f"\nTraining Accuracy: {train_acc * 100:.2f}%")
print(f"Testing Accuracy:  {test_acc * 100:.2f}%")
print(f"train-test accuracy gap:   {abs(train_acc - test_acc) * 100:.2f}%")

print("\nConfusion Matrix")
print(confusion_matrix(Y_test, Y_test_pred))

print("\nClassification Report")
print(classification_report(Y_test, Y_test_pred))

Y_test_prob = model.predict_proba(X_test)[:, 1]

plt.figure(figsize=(6, 5))
plt.scatter(Y_test + np.random.normal(0, 0.04, len(Y_test)), Y_test_prob, alpha=0.6)
plt.axhline(0.5, color='red', linestyle='--', label='Decision threshold (0.5)')
plt.xticks([0, 1], ['Rejected', 'Approved'])
plt.xlabel('Actual')
plt.ylabel('Predicted probability of approval')
plt.title('Actual vs Predicted Probability')
plt.legend()
plt.show()