# GUI
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QGridLayout, QPushButton, QLineEdit, QLabel, QToolBar, QFileDialog
from PyQt6.QtGui import QPixmap, QIcon, QIntValidator
from PyQt6.QtCore import Qt, QRect
# Mail Sender
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        # self.email = None
        # self.cc = None
        # self.appPassword = None
        # self.numberEmail = 5
        # self.filePath = None

        self.setWindowIcon(QIcon("images/calmunLogo.png"))
        self.setWindowTitle("CalMUN Ömer Bekir Girgin")
        self.setFixedSize(800, 600)

        layout = QGridLayout()

        title = QLabel("Ömer Bekir Girgin - Ö.B.G")

        emailLabel = QLabel("Kullanıcı Email:")
        self.emailInput = QLineEdit()
        self.emailInput.setPlaceholderText("Kendi mail adresini gir! (dumanemir299@gmail.com)")

        ccEmailLabel = QLabel("CC Email:")
        ccEmailInput = QLineEdit()
        ccEmailInput.setPlaceholderText("CC olarak eklemek istediğin mail adresini gir!")

        appPasswordLabel = QLabel("Uygulama Şifresi:")
        appPasswordInput = QLineEdit()
        appPasswordInput.setPlaceholderText("Google hesabından oluşturacağın Uygulama Şifreni gir!")

        numberEmailLabel = QLabel("Mail Sayısı:")
        numberEmailInput = QLineEdit()
        numberEmailInput.setPlaceholderText("Atmak istediğin mail sayısını gir. Çok fazla girmeni önermem!")
        int_only = QIntValidator()
        numberEmailInput.setValidator(int_only)
        numberEmailInput.textChanged.connect(self.sendMailButtonText)

        fileButton = QPushButton("Dosya Ekle")
        fileButton.clicked.connect(self.fileButtonClicked)

        self.sendMailButton = QPushButton(f"0 Tane Mail Yolla")
        self.sendMailButton.clicked.connect(self.getInformation)

        layout.addWidget(title, 0, 0, 1, 4, alignment=Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(emailLabel, 1, 0, 1, 1)
        layout.addWidget(self.emailInput, 1, 1, 1, 2)
        layout.addWidget(ccEmailLabel, 2, 0, 1, 1)
        layout.addWidget(ccEmailInput, 2, 1, 1, 2)
        layout.addWidget(appPasswordLabel, 3, 0, 1, 1)
        layout.addWidget(appPasswordInput, 3, 1, 1, 2)
        layout.addWidget(numberEmailLabel, 4, 0, 1, 1)
        layout.addWidget(numberEmailInput, 4, 1, 1, 2)
        layout.addWidget(fileButton, 2, 3, 2, 1, alignment=Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(self.sendMailButton, 5, 0, 1, 4, alignment=Qt.AlignmentFlag.AlignCenter)

        centerWidget = QWidget()
        centerWidget.setLayout(layout)
        self.setCentralWidget(centerWidget)

    def sendMailButtonText(self, newText):
        self.sendMailButton.setText(f"{newText} Tane Mail Yolla!")

    def fileButtonClicked(self):
        dlg = QFileDialog()
        dlg.setNameFilters(["*.txt", "*.csv"])
        dialogSuccessful = dlg.exec()

        if dialogSuccessful == 1:
            self.selectedFile = dlg.selectedFiles()

    def sendEmails(self):
        pass



app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()