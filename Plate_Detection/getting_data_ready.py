import os 
import pandas as pd
from xml.dom import minidom

class Project:
    def __init__(self, project_path):
        self.project_path = project_path
        self.bndbox_cords = []

        # Getting .png and .xml paths as .txt files   
        self.annotations_path = self.project_path + '/annotations'
        self.images_path = self.project_path + '/images'



    def control(self):
        self.saving_paths()
        self.get_bndbox_cords(self.project_path + "/annotations.txt")
        self.df_to_csv()



    def saving_paths(self):
        with open(self.project_path + '/annotations.txt', 'a') as f:
            for _, _, files in os.walk(self.annotations_path):
                for file in files:
                    f.write(self.annotations_path + '/' + str(file) + '\n')
            
        with open(self.project_path + '/images.txt', 'a') as f:
            for _, _, files in os.walk(self.images_path):
                for file in files:
                    f.write(self.images_path + '/' + str(file) + '\n')



    def get_bndbox_cords(self, annotations_path):
        with open(annotations_path, 'r') as file:
            lines = file.readlines()
            for path in lines:
                path = path.strip()
                if path:  # ensure the path is not empty
                    xmlfile = minidom.parse(path)

                    filename = xmlfile.getElementsByTagName('filename')[0].firstChild.data
                    ymin = xmlfile.getElementsByTagName('ymin')[0].firstChild.data
                    ymax = xmlfile.getElementsByTagName('ymax')[0].firstChild.data
                    xmin = xmlfile.getElementsByTagName('xmin')[0].firstChild.data
                    xmax = xmlfile.getElementsByTagName('xmax')[0].firstChild.data

                    self.bndbox_cords.append([filename, float(xmin), float(ymin), float(xmax), float(ymax)])



    def df_to_csv(self):
        df = pd.DataFrame(self.bndbox_cords, columns=['FileName', 'X_min', 'Y_min', 'X_max', 'Y_max'], index=None)
        df.to_csv(os.path.join(self.project_path, 'bounding_box.csv'))

plate_detection = Project('C:/Yazilim/utkuevkaya/Plate_Detection')
plate_detection.control()