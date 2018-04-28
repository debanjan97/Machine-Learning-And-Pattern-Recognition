#knn from scratch
import csv
import random
import math
import operator
import matplotlib.pyplot as plt
def loadDataset(split,trainingSet=[],testSet=[]):
    with open('/home/3y3X0r3/work/ML/Dataset/iris.csv','rt') as file:
        lines = csv.reader(file)
        dataset = list(lines)
        for x in range(len(dataset)):
            for y in range(4):
                dataset[x][y] = float(dataset[x][y])
            if random.random() < split:
                trainingSet.append(dataset[x])
            else:
                testSet.append(dataset[x])
        pltx=[]
        plty=[]
        for x in range(len(dataset)):
            pltx.append(dataset[x][2])
            plty.append(dataset[x][4])
        plt.scatter(pltx,plty)
        plt.show()



def euclideanDistance(list1,list2):
    distance = 0;
    for x in range(4):
        distance += pow(list1[x] - list2[x],2)
    return math.sqrt(distance)

def getNeighbours(trainingSet,testCase,k):
    distances=[]
    for x in range(len(trainingSet)):
        d = euclideanDistance(trainingSet[x],testCase)
        distances.append([trainingSet[x],d])
    distances.sort(key=operator.itemgetter(1))
    neighbours=[]
    for x in range(k):
        neighbours.append(distances[x][0])
    return neighbours

def getResponse(neighbours):
    classes ={}
    for x in range(len(neighbours)):
        response = neighbours[x][-1]
        if response in classes:
            classes[response] += 1
        else:
            classes[response] = 1
    sortedVotes = sorted(classes.items(), key=operator.itemgetter(1), reverse=True)
    return sortedVotes[0][0]

def accuracy(testSet,predictions):
    count = 0
    for x in range(len(testSet)):
        if testSet[x][-1] == predictions[x]:
            count +=1
    return (count/float(len(testSet)))*100.0


def main():
    trainingSet=[]
    testSet=[]
    loadDataset(0.66,trainingSet,testSet)
    #print('Train'+repr(trainingSet))
    #print('Test'+repr(testSet))
    predictions = []
    for x in range(len(testSet)):
        neighbours = getNeighbours(trainingSet,testSet[x],5)
        result = getResponse(neighbours)
        predictions.append(result)
        print('Predicted='+repr(result)+', Actual='+testSet[x][-1]+'\n')
    acc = accuracy(testSet,predictions)
    print('Accuracy: '+repr(acc)+'%\n')

main()
