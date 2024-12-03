import matplotlib.pyplot as plt
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures

a=3

if a == 1:
    heights_AVL = []
    with open('avl_heights.txt', 'r') as file:
        for line in file:
            heights_AVL.append(int(line.strip()))

    keys = range(1, len(heights_AVL) + 1)
    plt.plot(keys, heights_AVL, label='h(key) для AVL дерева')
    plt.xlabel('Номер ключа')
    plt.ylabel('Высота дерева')
    plt.title('График зависимости АВЛ дерева от высоты')
    plt.grid(True)
    plt.show()

if a == 2:
    heights_RB = []
    with open('RBtree_heights.txt', 'r') as file:
        for line in file:
            heights_RB.append(int(line.strip()))

    keys = range(1, len(heights_RB) + 1)
    plt.plot(keys, heights_RB, label='h(key) для красно-черного дерева')
    plt.xlabel('Номер ключа')
    plt.ylabel('Высота дерева')
    plt.title('График зависимости красно-черного дерева от высоты')
    plt.grid(True)
    plt.show()

if a == 3:
        # Read data from the file
    with open('bst_heights.txt', 'r') as file:
        data = file.readlines()

    # Parse the data
    n_values = []
    h_values = []
    for line in data:
        n, h = map(int, line.split())
        n_values.append(n)
        h_values.append(h)

    # Convert lists to numpy arrays
    n_values = np.array(n_values).reshape(-1, 1)
    h_values = np.array(h_values)

    # Polynomial regression
    degree = 2  # You can adjust the degree of the polynomial
    poly_features = PolynomialFeatures(degree=degree)
    n_poly = poly_features.fit_transform(n_values)

    # Fit the polynomial regression model
    model = LinearRegression()
    model.fit(n_poly, h_values)

    # Predict the heights using the polynomial model
    h_pred = model.predict(n_poly)

    # Plot the data and the regression curve
    plt.scatter(n_values, h_values, color='blue', label='Data')
    plt.plot(n_values, h_pred, color='red', label='Polynomial Regression')
    plt.xlabel('Number of Keys (n)')
    plt.ylabel('Height of BST (h)')
    plt.title('Height of BST vs Number of Keys with Polynomial Regression')
    plt.legend()
    plt.grid(True)
    plt.show()

    # Print the coefficients of the polynomial regression
    coefficients = model.coef_
    intercept = model.intercept_
    print(f"Polynomial Regression Coefficients: {coefficients}")
    print(f"Intercept: {intercept}")

    # Function to represent the polynomial regression curve
    def polynomial_regression_curve(x, coefficients, intercept):
        y = intercept
        for i, coef in enumerate(coefficients):
            y += coef * x**(i+1)
        return y

    # Example usage of the polynomial regression curve function
    x_example = 1000
    y_example = polynomial_regression_curve(x_example, coefficients, intercept)
    print(f"Predicted height for n={x_example}: {y_example}")