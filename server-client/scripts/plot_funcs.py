import matplotlib.pyplot as plt


def plot_data(ax_1, ax_2, x):

    ax_1.clear()
    ax_1.set_ylim(-200, 200)
    ax_1.set_xlim(-200, 200)
    ax_1.scatter(x[0], x[2])

    ax_2.clear()
    ax_2.set_ylim(-200, 200)
    ax_2.set_xlim(-200, 200)
    ax_2.scatter(x[2], x[1])
