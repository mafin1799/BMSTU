from matplotlib import pyplot as plt


def dydx(x, y):
    return (x - y) / 2


def rungeKutta(x0, y0, x, h):
    n = int((x - x0) / h)
    y = y0
    xs = []
    ys = []
    for i in range(1, n + 1):
        k1 = h * dydx(x0, y)
        k2 = h * dydx(x0 + 0.5 * h, y + 0.5 * k1)
        k3 = h * dydx(x0 + 0.5 * h, y + 0.5 * k2)
        k4 = h * dydx(x0 + h, y + k3)
        y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4)
        x0 = x0 + h

        xs.append(x0)
        ys.append(y)
    return xs, ys
    # return y


def func(x, y):
    return (x - y) / 2


def euler(x0, y, x, h):
    temp = -0
    xs = []
    ys = []
    while x0 < x:
        temp = y
        y = y + h * func(x0, y)
        x0 = x0 + h
        xs.append(x0)
        ys.append(y)
    return xs, ys
    # print("Approximate solution at x = ", x, " is ", "%.6f " % y)



if __name__ == '__main__':
    x0 = 0
    y0 = 1
    x = 2
    h = 0.2
    print("Method Euler Y", len(euler(x0, y0, x, h)[1]))
    print("Method Euler X", len(euler(x0, y0, x, h)[0]))
    print("Method rungeKutta Y", len(rungeKutta(x0, y0, x, h)[1]))
    print("Method rungeKutta X", len(rungeKutta(x0, y0, x, h)[0]))
    X1 = euler(x0, y0, x, h)[0]
    Y1 = euler(x0, y0, x, h)[1]
    X2 = rungeKutta(x0, y0, x, h)[0]
    Y2 = rungeKutta(x0, y0, x, h)[1]

    fig, ax = plt.subplots()
    ax.plot(X1, Y1, color='green', label='Euler')
    ax.plot(X2, Y2, color='red', label='rungeKutta')
    ax.legend(loc='upper left')

    plt.show()
