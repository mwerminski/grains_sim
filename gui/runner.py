import subprocess, os, shutil, time
from datetime import datetime
from defines import ALLOWED_EXT
from collections import OrderedDict

class Runner:

    def __init__(self, program_path=""):
        self.done_tasks = OrderedDict()
        self.dir_name = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        splitted_path = program_path.split("/")
        os.chdir("/".join(splitted_path[:-1]))
        self.program_name = splitted_path[-1]
        print(program_path, " | ", self.program_name)

    def run_tasks(self):
        self.done_tasks = OrderedDict()
        self.dir_name = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        os.mkdir(self.dir_name)
        execution_time = "-1"
        for key, value in self.tasks.items():
            try:
                args = [f"./{self.program_name}"]
                args.extend(value.split(" "))
                time_started = time.time()
                subprocess.run(args, check=True)
                execution_time = str(time.time() - time_started)
            except subprocess.CalledProcessError as e:
                print(e)
                continue
            os.mkdir(os.path.join(os.getcwd(), self.dir_name, str(key)))

            for file in os.listdir(os.getcwd()):
                ext = os.path.splitext(file)[1][1:]
                if ext in ALLOWED_EXT:
                    shutil.move(os.path.join(os.getcwd(), file), os.path.join(os.getcwd(), self.dir_name, str(key), file))
            
            self.done_tasks[key] = f"{execution_time}s {value} {os.path.join(os.getcwd(), self.dir_name, str(key))}"
        print("DONE")
        return self.done_tasks

            
    def set_tasks(self, input_tasks=dict()):
        self.tasks = input_tasks
