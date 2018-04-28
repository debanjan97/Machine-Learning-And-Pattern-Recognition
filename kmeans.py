import pandas as pd
from sklearn.cluster import KMeans
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import style
from sklearn.decomposition import PCA as sklearnPCA

dataset = pd.read_csv('./Dataset/iris2.csv')
dataset = np.array(dataset.drop('variety',axis = 1))
size = len(dataset)
clf = KMeans(n_clusters=3)
clf.fit(dataset)

centroids = clf.cluster_centers_
labels = clf.labels_

colors = ["r","b","g"]

print(repr(centroids))
pca = sklearnPCA(n_components = 2)
mod_dataset = np.array(pd.DataFrame(pca.fit_transform(dataset)))

#print(mod_dataset)

for i in range (size):
    plt.scatter(mod_dataset[i][0],mod_dataset[i][1],color=colors[labels[i]])
##plt.scatter(mod_centroid[:,0],mod_centroid[:,1],marker='x',s=150) ##debatable
plt.show()
