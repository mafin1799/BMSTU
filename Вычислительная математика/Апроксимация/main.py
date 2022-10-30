from matplotlib import pyplot as plt
import numpy as np


def export(filename):
    opora = []
    with open(filename) as f:
        for line in f:
            opora.append(float(line))
        return opora


def sred(array):
    return sum(array) / len(array)


def MNK(x, y):
    mx = sum(x) / len(x)
    my = sum(y) / len(y)
    a2 = np.dot(x, x) / len(x)
    a11 = np.dot(x, y) / len(x)
    kk = (a11 - mx * my) / (a2 - mx ** 2)
    bb = my - kk * mx

    ya = []

    for i in (x):
        ya.append(kk * i + bb)
    print("k = ", kk, "b = ", bb)
    return ya


def lab2():
    x = (export("Opora"))
    y = [sred(export("h720")), sred(export("h730")), sred(export("h740")), sred(export("h750")), sred(export("h760")),
         sred(export("h767"))]
    print(y)
    plt.plot(x, y, c='red')
    plt.plot(x, MNK(x, y))
    # print(type(x))
    # print(type(y))
    plt.show()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    lab2()
# See PyCharm help at https://www.jetbrains.com/help/pycharm/
