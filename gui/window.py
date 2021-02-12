
from PyQt5.QtWidgets import QApplication, QListWidget, QWidget, QPushButton, QVBoxLayout, QLineEdit, QCheckBox, QComboBox, QDialog, QFileDialog
import matplotlib.pyplot as plt 
from defines import AVAILABLE_DIMENSIONS, AVAILABLE_METHODS, AVAILABLE_NEIGHBOURHOODS
from collections import OrderedDict
from functools import partial
import os

class Window(QWidget):

    def __init__(self, controller):
        super().__init__()
        self.controller = controller
        self.buttons_enabled = True
        self.layout = QVBoxLayout()
        self.__init_list()
        self.__init_box()
        self.__init_button()
        self.setLayout(self.layout)


    def __init_list(self):
        self.task_list = QListWidget()
        self.done_list = QListWidget()
        self.layout.addWidget(self.task_list)
        self.layout.addWidget(self.done_list)
        self.task_list.addItem("  ")

    def __init_button(self):
        self.load_button = QPushButton('Load tasks')
        self.load_button.clicked.connect(self.__load_tasks)
        self.add_button = QPushButton('Add task')
        self.add_button.clicked.connect(self.__add_task)
        self.run_button = QPushButton('Run tasks')
        self.run_button.clicked.connect(self.controller.run_tasks)
        self.image_button = QPushButton('Generate 3D chart')
        self.image_button.clicked.connect(self.__create_chart)
        self.image_button2 = QPushButton('Generate 2D charts')
        self.image_button2.clicked.connect(self.__create_charts)
        self.delete_button = QPushButton('Delete selected task')
        self.delete_button.clicked.connect(self.__delete_task)
        self.exit_button = QPushButton('Exit')
        self.exit_button.clicked.connect(self.__exit)

        self.layout.addWidget(self.load_button)
        self.layout.addWidget(self.add_button)
        self.layout.addWidget(self.run_button)
        self.layout.addWidget(self.image_button)
        self.layout.addWidget(self.image_button2)
        self.layout.addWidget(self.delete_button)
        self.layout.addWidget(self.exit_button)

    def __init_box(self):
        self.neighbourhood = QComboBox()
        self.method = QComboBox()
        self.dimension = QComboBox()
        self.neighbourhood.addItems(AVAILABLE_NEIGHBOURHOODS)
        self.dimension.addItems(AVAILABLE_DIMENSIONS)
        self.method.addItems(AVAILABLE_METHODS)

        self.x = QLineEdit(placeholderText="X")
        self.y = QLineEdit(placeholderText="Y")
        self.z = QLineEdit(placeholderText="Z")
        self.iterations = QLineEdit(placeholderText="Iterations")
        self.initial_grain_num = QLineEdit(placeholderText="Initial grain number")
        self.periodic = QCheckBox()
        self.periodic.setText("Periodic")

        self.layout.addWidget(self.neighbourhood)
        self.layout.addWidget(self.method)
        self.layout.addWidget(self.dimension)
        self.layout.addWidget(self.x)
        self.layout.addWidget(self.y)
        self.layout.addWidget(self.z)
        self.layout.addWidget(self.iterations)
        self.layout.addWidget(self.initial_grain_num)
        self.layout.addWidget(self.periodic)

    def __read_params(self):
        return OrderedDict([
            ("Neighbourhood", self.neighbourhood.currentText()),
            ("Method", self.method.currentText()),
            ("Iterations", self.iterations.text()),
            ("InitGrainNum", self.initial_grain_num.text()),
            ("Dimension", self.dimension.currentText()),
            ("x", self.x.text()),
            ("y", self.y.text()),
            ("z", self.z.text()),
            ("Periodic", str(self.periodic.isChecked()))
        ])
    
    def __add_task(self):
        task = self.__read_params()
        text = " ".join(task.values())
        self.task_list.addItem(text)

    def __load_tasks(self):
        task = self.__read_params()
        fname = QFileDialog.getOpenFileName(self, 'Open file', '~/',"Input files (*.txt *.cfg)")[0]
        if fname != "":
            with open(fname) as file:
                for line in file:
                    self.task_list.addItem(line.strip("\n"))

    def __create_chart(self):
        item = self.done_list.currentItem()
        if item:
            dir_path = item.text().split(" ")[-1]
            for file in os.listdir(dir_path):
                ext = os.path.splitext(file)[1][1:]
                if ext == "csv":
                    self.controller.create_chart(os.path.join(dir_path, file))

    def __create_charts(self):
        item = self.done_list.currentItem()
        if item:
            dir_path = item.text().split(" ")[-1]
            for file in os.listdir(dir_path):
                ext = os.path.splitext(file)[1][1:]
                if ext == "csv":
                    self.controller.create_charts(os.path.join(dir_path, file))
        
    def __delete_task(self):
        item = self.task_list.currentRow()
        if item:
            self.task_list.takeItem(item)

    def __exit(self):
        exit()

    def add_done_task(self, tasks):
        for task in tasks.values():
            self.done_list.addItem(task)

    def get_tasks(self):
        result = dict()
        num_of_tasks = self.task_list.count() - 1
        for task_id in range(num_of_tasks):
            result[task_id] = self.task_list.item(task_id + 1).text()
        return result

    def change_buttons_state(self): 
        self.buttons_enabled = not self.buttons_enabled

        self.add_button.setEnabled(self.buttons_enabled)
        self.run_button.setEnabled(self.buttons_enabled)
        self.image_button.setEnabled(self.buttons_enabled)

        self.task_list.setEnabled(self.buttons_enabled)
        self.done_list.setEnabled(self.buttons_enabled)

        self.neighbourhood.setEnabled(self.buttons_enabled)
        self.method.setEnabled(self.buttons_enabled)
        self.dimension.setEnabled(self.buttons_enabled)
        self.x.setEnabled(self.buttons_enabled)
        self.y.setEnabled(self.buttons_enabled)
        self.z.setEnabled(self.buttons_enabled)
        self.iterations.setEnabled(self.buttons_enabled)
        self.initial_grain_num.setEnabled(self.buttons_enabled)
        self.periodic.setEnabled(self.buttons_enabled)

