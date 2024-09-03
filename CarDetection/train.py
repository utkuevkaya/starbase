from prepare import Prepare
import cv2 as cv
import logging
import os
from ultralytics import YOLO

logging.basicConfig(filename="log.log", format="%(asctime)s %(message)s", filemode="w")
logger = logging.getLogger()
logger.setLevel(logging.INFO)

model = YOLO("yolov8n.yaml")

main_dir = r"C:\Yazilim\utkuevkaya\CarDetection"
images_dir = r"C:\Yazilim\utkuevkaya\CarDetection\data\training_images"
csv_dataset = r"C:\Yazilim\utkuevkaya\CarDetection\data\train_solution_bounding_boxes (1).csv"
image_save = r"C:\Yazilim\utkuevkaya\CarDetection\data\dataset\images"
text_save = r"C:\Yazilim\utkuevkaya\CarDetection\data\dataset\labels"

image_size = cv.imread(os.path.join(images_dir, "1040.jpg")).size

prepare = Prepare()
files = prepare.get_file_names(extension="jpg", images_dir=images_dir, is_sorted=False)
prepare.prepare_dataset(images_dir=images_dir, bbox_file=csv_dataset, image_files=files, 
                        images_save_dir=image_save, txt_save_dir=text_save)

logger.info("Preparation Sucessfull!")

model.train(data=r"C:\Yazilim\utkuevkaya\CarDetection\dataset.yaml",
            epochs=30,
            imgsz=640,
            name="custom_model",
            workers=2)

logger.info("Model has trained")