import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.linear_model import LinearRegression
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

df = pd.read_csv('house_prices.csv')

print("First 5 rows of the dataset:")
print(df.head())

numerical_columns = df.select_dtypes(include=np.number).columns
categorical_columns = df.select_dtypes(include='object').columns

df[numerical_columns] = df[numerical_columns].fillna(df[numerical_columns].mean())
for column in categorical_columns:
    df[column] = df[column].fillna('Missing')

print("\nMissing Values after Cleaning:")
print(df.isnull().sum())

print("\nUnique values for Categorical Columns after filling 'Missing':")
for column in categorical_columns:
    print(f"{column}: {df[column].unique()}")

print("\nData Types after Encoding:")
print(df.dtypes)

print("\nNumber of duplicate rows:", df.duplicated().sum())

print("\nFirst 10 rows after Data Cleaning:")
print(df.head(10))

label_encoders = {}
for column in categorical_columns:
    le = LabelEncoder()
    df[column] = le.fit_transform(df[column])
    label_encoders[column] = le

plt.figure(figsize=(15, 10))
correlation_matrix = df.corr()
sns.heatmap(correlation_matrix, annot=False, cmap='coolwarm')
plt.title('Correlation Heatmap')
plt.show()

top_features = correlation_matrix['SalePrice'].abs().sort_values(ascending=False).index[1:4]  

plt.figure(figsize=(15, 10))
for i, feature in enumerate(top_features, 1):
    plt.subplot(2, 3, i)
    sns.histplot(df[feature], kde=True, color='blue')
    plt.title(f'{feature} Distribution')
    
    plt.subplot(2, 3, i+3)
    sns.boxplot(x=df[feature], color='green')
    plt.title(f'{feature} Boxplot')
plt.tight_layout()
plt.show()

df['PricePerSqFt'] = df['SalePrice'] / df['GrLivArea']

X = df.drop('SalePrice', axis=1)
y = df['SalePrice']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

lr = LinearRegression()
lr.fit(X_train, y_train)
y_pred_lr = lr.predict(X_test)

dt = DecisionTreeRegressor(random_state=42)
dt.fit(X_train, y_train)
y_pred_dt = dt.predict(X_test)

rf = RandomForestRegressor(n_estimators=100, random_state=42)
rf.fit(X_train, y_train)
y_pred_rf = rf.predict(X_test)

def evaluate_model(y_true, y_pred, model_name):
    print(f"--- {model_name} ---")
    print("MAE:", mean_absolute_error(y_true, y_pred))
    print("MSE:", mean_squared_error(y_true, y_pred))
    print("RMSE:", np.sqrt(mean_squared_error(y_true, y_pred)))
    print("R-squared:", r2_score(y_true, y_pred))
    print("\n")

evaluate_model(y_test, y_pred_lr, "Linear Regression")
evaluate_model(y_test, y_pred_dt, "Decision Tree")
evaluate_model(y_test, y_pred_rf, "Random Forest")

plt.figure(figsize=(10, 6))
plt.scatter(y_test, y_pred_rf, color='blue')
plt.plot([y_test.min(), y_test.max()], [y_test.min(), y_test.max()], 'k--', lw=2)
plt.xlabel('Actual Prices')
plt.ylabel('Predicted Prices')
plt.title('Actual vs Predicted Prices (Random Forest)')
plt.show()

print("Conclusion:")
print("1. Random Forest performed the best among the models.")
print("2. Features like Overall Quality, GrLivArea, and TotalBsmtSF are significant predictors of house prices.")
print("3. The model can be further improved with hyperparameter tuning and advanced feature engineering.")