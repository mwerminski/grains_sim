import csv, math
import numpy as np

class CSVReader:
    def __init__(self, file_name):
        self.cells = list()
        self.dimension = list()
        with open(file_name) as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            self.dimension = list(map(int, next(reader)))
            z = self.dimension[2]
            y = self.dimension[1]
            if z == 0:
                z = 1
            xy = self.dimension[0] * self.dimension[1]
            num_of_cells = xy*z
            plane = list()
            for i, row in enumerate(reader):
                converted_row = list(map(int, row))
                plane.append(converted_row)
                if (i + 1) % y == 0:
                    self.cells.append(plane)
                    plane = list()

        
        # print(self.dimension)

                




