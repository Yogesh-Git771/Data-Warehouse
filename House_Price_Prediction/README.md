
# 🏠 House Price Prediction System

This project is a machine learning-based solution to predict house prices using a real-world dataset. The model analyzes housing attributes like living area, basement area, and quality to estimate property value. Multiple regression models are trained and compared for performance evaluation.

---

## 📌 Features

- ✅ Data cleaning and preprocessing (handling missing values, duplicates)
- ✅ Encoding categorical variables
- ✅ Feature engineering (`PricePerSqFt`)
- ✅ Visualizations:
  - Correlation heatmap
  - Histograms & Boxplots for top features
  - Actual vs Predicted scatter plot
- ✅ Models used:
  - Linear Regression
  - Decision Tree Regressor
  - Random Forest Regressor
- ✅ Evaluation Metrics:
  - MAE, MSE, RMSE
  - R² Score

---

## 📊 Technologies Used

- Python
- NumPy, Pandas
- Seaborn, Matplotlib
- Scikit-learn

---

## 📁 File Structure

```
House_Price_Prediction/
├── project.py              # Main Python script for preprocessing, training & evaluation
├── house_prices.csv        # Dataset file used for model training/testing
└── README.md               # This file – explains project purpose and structure
```

---

## 🚀 How to Run

1. Install the required libraries:
```bash
pip install pandas numpy matplotlib seaborn scikit-learn
```

2. Run the script:
```bash
python project.py
```

> Make sure `house_prices.csv` is in the same directory as `project.py`.

---

## 📈 Results Summary

- 🔹 Best Performing Model: **Random Forest Regressor**
- 🔹 Key Influencing Features: `OverallQual`, `GrLivArea`, `TotalBsmtSF`
- 🔹 The model's predictions closely align with actual prices as shown in the scatter plot

---


