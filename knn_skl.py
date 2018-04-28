import pandas as pd
import numpy as np
from sklearn import cross_validation, preprocessing, neighbors, svm
from sklearn.linear_model import LinearRegression
dataset = pd.read_csv('./Dataset/iris2.csv')
#print(dataset.head())

X = np.array(dataset.drop(['variety'],axis = 1))
print(X)
X = preprocessing.scale(X)
print(X)
y = np.array(dataset['variety'])

X_train, X_test, y_train, y_test = cross_validation.train_test_split(X,y,test_size=0.3)
clf = neighbors.KNeighborsClassifier()
clf.fit(X_train,y_train)
accuracy = clf.score(X_test,y_test)
print(accuracy)
