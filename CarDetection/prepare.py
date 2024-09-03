import os 
from pathlib import Path
import pandas as pd
import cv2 as cv


class Prepare:

    def __init__(self, main_dir: Path):
        self.main_dir = main_dir
        os.chdir(self.main_dir)

    
    def get_file_names(self, extension: str, images_dir: Path, is_sorted = True):
        if "." not in extension:
            extension = "." + extension

        valid_extension = [".png", ".jpg", ".jpeg"]
        if extension not in valid_extension:
            raise Exception("The file extension must be png, jpg or jpeg")


        previous_files = os.listdir(images_dir)
        files = [] 

        for file in previous_files:
            file_num, ext = os.path.splitext(file)
            
            if ext == extension:
                file_num = int(file_num)
                files.append(file_num)
            else:
                continue

        if is_sorted:        
            files = sorted(files)

        return files
    


    def animation(self, files:list, images_dir:Path, waitMilliseconds:int):
        os.chdir(images_dir)
        images = []
        
        for file in files:
            image = str(file) + ".jpg"
            img = cv.imread(image)
            images.append(img)

        for image in images:
            cv.imshow("Video", image)
            cv.waitKey(waitMilliseconds)



    def prepare_dataset(self, images_dir:Path, bbox_file:Path, image_files:list, images_save_dir:Path, txt_save_dir:Path):
        sampleImg = str(image_files[0]) + ".jpg"
        sampleImg = cv.imread(os.path.join(images_dir, sampleImg))
        imageH, imageW, imageC = sampleImg.shape 

        bbox_dataset = pd.read_csv(bbox_file)

        # Create empty file for all images
        for img in image_files:
            with open(os.path.join(txt_save_dir, str(img) + ".txt"), "w") as f:
                pass

        # Prepare for training
        for index, row in bbox_dataset.iterrows():
            file_name = row["image"]
            xmin, ymin, xmax, ymax = row["xmin"], row["ymin"], row["xmax"], row["ymax"]

            x_center, y_center = ((xmax+xmin)/2)/imageW, ((ymax+ymin)/2)/imageH
            width, height = (xmax-xmin)/imageW, (ymax-ymin)/imageH 

            file_num = file_name.split("_")[-1].split(".")[0]
            with open(os.path.join(txt_save_dir, file_num + ".txt"), "a") as f:
                f.write(f"0 {x_center} {y_center} {width} {height}")


        # Move Images to the right directory
        for image in image_files:
            old_path = os.path.join(images_dir, str(image) + ".jpg")
            new_path = os.path.join(images_save_dir, str(image) + ".jpg")
            os.rename(old_path, new_path)