# Machine Learning Lab: Classification using Linear Discriminant Analysis (LDA)

## 1. Concept of Linear Discriminant Analysis (LDA)

**Linear Discriminant Analysis (LDA)** is a supervised dimensionality reduction and classification technique. While techniques like Principal Component Analysis (PCA) find directions that maximize variance (regardless of class), LDA finds a feature space that **maximizes class separability**.

### Key Objectives:
- **Maximize the distance between means** of different classes (Between-class variance).
- **Minimize the variation within each class** (Within-class variance).

### Why use LDA for this dataset?
The Seattle Weather dataset contains multiple numerical features (precipitation, temperature, wind) that contribute to a specific weather "class." LDA is ideal here because:
1.  It helps visualize how these features distinctively separate weather types (e.g., Rain vs. Sun).
2.  It creates a robust linear classifier by assuming the data follows a Gaussian distribution with shared covariance.

---

## 2. Notebook Walkthrough and Code Explanation

The implementation is divided into four logical parts, as requested in the lab assignment.

### Part A: Data Preparation
We start by loading the dataset and isolating the predictive features. The `date` column is dropped as it doesn't represent a physical measurement for LDA.
```python
# Standardizing features is crucial as LDA is sensitive to the scale of input data
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)
```
**Rationale:** Standardizing ensures that features with larger ranges (like precipitation) don't dominate the discriminant components incorrectly.

### Part B: LDA Implementation (Dimensionality Reduction)
We transform the 4D feature space into a 2D space for visualization.
```python
lda_transform = LinearDiscriminantAnalysis(n_components=2)
X_lda = lda_transform.fit_transform(X_scaled, y_encoded)
```
**Rationale:** Reducing to 2 components allows us to plot the classes on a 2D plane and visually inspect how well the weather types are separated.

### Part C: Classification
We split the data (80% training, 20% testing) and train a `LinearDiscriminantAnalysis` classifier.
```python
lda_clf = LinearDiscriminantAnalysis()
lda_clf.fit(X_train, y_train)
y_pred = lda_clf.predict(X_test)
```

### Part D: Performance Evaluation
We evaluate the model using accuracy, a confusion matrix, and classification reports.

---

## 3. Results and Visualization

### Model Performance
- **Overall Accuracy:** ~70%
- **Insights:** The model performs very well at distinguishing between **Rain** and **Sun**, but struggles with infrequent classes like **Drizzle** or **Snow**, which often get misclassified due to overlapping feature ranges.

### Visualizations

#### 1. LDA Feature Space (2D Projection)
This plot shows the separation achieved by the two most significant discriminant components.
![LDA Visualization](./results/lda_visualization.png)

#### 2. Confusion Matrix
The heatmap indicates where the model's predictions align with the actual labels.
![Confusion Matrix](./results/confusion_matrix.png)

---

## 4. Summary of Observations
1.  **Dimensionality Reduction:** LDA successfully reduced the complexity of the data while maintaining the essential features that distinguish weather types.
2.  **Class Imbalance:** The dataset is heavily skewed towards 'Rain' and 'Sun', which is reflected in the high recall for these classes compared to others.
3.  **Linearity:** The accuracy suggests that while linear boundaries are effective, there may be overlapping distributions that LDA cannot fully capture.
