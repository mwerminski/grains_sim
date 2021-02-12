import matplotlib.pyplot as plt
import numpy as np
import sys, csv, reader
from datetime import datetime


class Chart:
    def __init__(self, cells=list(), path="chart.png"):
        self.cells = np.asarray(cells)
        self.path = path

    def create_plot(self):
        fig = plt.figure()
        ax = fig.gca(projection='3d', alpha=1)
        cmap = plt.get_cmap("gist_rainbow")
        norm = plt.Normalize( self.cells.min(), self.cells.max())
        colormap = cmap(norm( self.cells))
        ax.voxels(np.ones_like( self.cells), facecolors=colormap, edgecolor="none", shade=False)
        ax.view_init(20, 45)
        plt.savefig(self.path)
        plt.show(block=False)


class ChartBeta:
    def __init__(self, cells=list(), path="chart.png"):
        self.cells = np.asarray(cells)
        self.path = path

    def create_plot(self):
        fig, axarr = plt.subplots(3,4)
        x, y, z = self.cells.shape
        cmap = plt.get_cmap("gist_rainbow")
        norm = plt.Normalize(self.cells.min(), self.cells.max())
        front = np.vsplit(self.cells, x)[0].reshape(y, z)
        top = np.hsplit(self.cells, y)[0].reshape(x, z)[::-1]
        right = np.dsplit(self.cells, z)[-1].transpose(2,0,1).transpose(2,0,1).reshape(y, x)
        left = np.dsplit(self.cells, z)[0].transpose().reshape(y, x)[:, ::-1]
        bottom = np.hsplit(self.cells, y)[-1].reshape(x, z)
        back = np.vsplit(self.cells, x)[-1].reshape(y, z)[:, ::-1]

        axarr[0][1].imshow(top, cmap=cmap, norm=norm)
        axarr[1][1].imshow(front, cmap=cmap, norm=norm)
        axarr[1][2].imshow(right, cmap=cmap, norm=norm)
        axarr[1][0].imshow(left, cmap=cmap, norm=norm)
        axarr[1][3].imshow(back, cmap=cmap, norm=norm)
        axarr[2][1].imshow(bottom, cmap=cmap, norm=norm)
        for i in range(0, 4):
            for j in range(0, 3):
                axarr[j][i].axis('off') 
        # fig.delaxes(axarr[0][1])
        plt.savefig(self.path)
        plt.show(block=False)

if __name__ == "__main__":

    data_path = sys.argv[1]
    print("file ", data_path)
    handler = reader.CSVReader(data_path)
    chart = Chart(handler.cells, data_path + ".png")
    chart.create_plot()




       

    