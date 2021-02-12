from PyQt5.QtWidgets import QApplication
import window, runner, time, charts, reader
from datetime import datetime


PROGRAM_PATH = "/home/szylkret/CLionProjects/grains/cmake-build-release/grains"

class Controller:

    def __init__(self):
        self.app = QApplication([])
        self.main_window = None
        self.runner = runner.Runner(program_path=PROGRAM_PATH)
        self.__create_window()

    def __create_window(self):
        self.app.setStyle('Fusion')
        self.main_window = window.Window(self)
        self.main_window.update()
        self.main_window.show()
        self.app.exec_()

    def run_tasks(self):
        self.main_window.change_buttons_state()
        self.runner.set_tasks(self.main_window.get_tasks())
        done_tasks = self.runner.run_tasks()
        self.main_window.add_done_task(done_tasks)
        self.main_window.change_buttons_state()

    def create_chart(self, file_path):
        date = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        self.main_window.change_buttons_state()
        handler = reader.CSVReader(file_path)
        chart_path = "/".join(file_path.split("/")[:-1])+f"/{date}_chart.png"
        chart = charts.Chart(handler.cells, chart_path).create_plot()
        self.main_window.change_buttons_state()

    def create_charts(self, file_path):
        date = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        self.main_window.change_buttons_state()
        handler = reader.CSVReader(file_path)
        chart_path = "/".join(file_path.split("/")[:-1])+f"/{date}_chart.png"
        chart = charts.ChartBeta(handler.cells, chart_path).create_plot()
        self.main_window.change_buttons_state()
