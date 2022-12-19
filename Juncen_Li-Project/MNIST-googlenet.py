import torch
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
import os
import time
from models import *

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

def load():

    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize([0.5], [0.5]),
    ])

    train_set = torchvision.datasets.MNIST(root='./MNIST-dataset', train=True,
                                             download=True, transform=transform)
    train_loader = torch.utils.data.DataLoader(train_set, batch_size=128,
                                               shuffle=True, num_workers=2)

    test_set = torchvision.datasets.MNIST(root='./MNIST-dataset', train=False,
                                            download=True, transform=transform)
    test_loader = torch.utils.data.DataLoader(test_set, batch_size=128,
                                              shuffle=False, num_workers=2)

    return train_loader, test_loader


def test(net, inputs, criterion=None):
    net.eval()
    correct = 0
    total = 0
    total_loss = 0
    with torch.no_grad():
        for data in inputs:
            images, labels = data[0].repeat(1,3,1,1), data[1]
            
            images, labels = images.to(device), labels.to(device)

            outputs = net(images)
            _, predicted = torch.max(outputs.data, 1)
            total_loss += criterion(outputs, labels)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    acc = format((100 * correct / total), '.4f')
    loss = format((total_loss / len(inputs)), '.4f')
    return acc, loss

def train(total_epoch):
    
    print(device)
    train_loader, test_loader = load()
    net = googlenet()

    net.to(device)

    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(net.parameters(), lr=0.001)
    # loop over the dataset multiple times
    best_test_acc = 0
    print('Loop\t\tTrain Loss\t\tTrain Acc %\t\tTest Loss\t\tTest Acc  %')
    # get the startTime
    start = time.time()

    for epoch in range(total_epoch):
        # get the inputs; data is a list of [inputs, labels]
        for i, data in enumerate(train_loader, 0):
            net.train()
            
            inputs = data[0].repeat(1,3,1,1)
            labels = data[1]
            inputs, labels = inputs.to(device), labels.to(device)

            optimizer.zero_grad()  # gradient set to zero
            outputs = net(inputs)
            loss = criterion(outputs, labels)
            loss.backward() #backword
            optimizer.step()
        # print statistics
        train_accuracy, train_loss = test(net, train_loader, criterion)
        test_accuracy, test_loss = test(net, test_loader,criterion)
        if epoch%(total_epoch/10) == 0 or epoch == total_epoch-1:
                if total_epoch<100 and epoch<10:
                    print(epoch + 1, '/', total_epoch, '\t\t', train_loss, '\t\t', train_accuracy,
                        '\t\t', test_loss, '\t\t', test_accuracy)
                else:
                    print(epoch + 1, '/', total_epoch, '\t', train_loss, '\t\t', train_accuracy,
                          '\t\t', test_loss, '\t\t', test_accuracy)
        if best_test_acc < float(test_accuracy):
            best_test_acc = float(test_accuracy)
            if not os.path.isdir('./model'):
                os.mkdir('./model')
            torch.save(net.state_dict(), "./model/MNIST_googlenet_CNN.ckpt")
    
    end = time.time();
    print("The training time of MNIST googlenet pytorch is:", end-start,"(seconds)")
    print('Model saved in file: ./model/MNIST_googlenet_CNN.ckpt')

#Main
if __name__ == '__main__':

    epoch = 10
    train(epoch)

        

