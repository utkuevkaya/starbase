# GUI
import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget, QGridLayout, QPushButton, QLineEdit, QLabel, QToolBar, QFileDialog
from PyQt6.QtGui import QPixmap, QIcon, QIntValidator
from PyQt6.QtCore import Qt, QRect
from mailSender import MailSender
import pandas as pd 

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # INIT
        self.setWindowIcon(QIcon("images/calmunLogo.png"))
        self.setWindowTitle("CalMUN Ömer Bekir Girgin")
        self.setFixedSize(800, 600)

        layout = QGridLayout()

        title = QLabel("Ömer Bekir Girgin - Ö.B.G")

        # USER MAIL
        emailLabel = QLabel("Kullanıcı Email:")
        self.emailInput = QLineEdit()
        self.emailInput.setPlaceholderText("Kendi mail adresini gir! (dumanemir299@gmail.com)")

        # CC MAIL ADRESS
        ccEmailLabel = QLabel("CC Email:")
        self.ccEmailInput = QLineEdit()
        self.ccEmailInput.setPlaceholderText("CC olarak eklemek istediğin mail adresini gir!")

        # APP PASSWORD
        appPasswordLabel = QLabel("Uygulama Şifresi:")
        self.appPasswordInput = QLineEdit()
        self.appPasswordInput.setPlaceholderText("Google hesabından oluşturacağın Uygulama Şifreni gir!")

        # NUMBER OF MAILS 
        numberEmailLabel = QLabel("Mail Sayısı:")
        self.numberEmailInput = QLineEdit()
        self.numberEmailInput.setPlaceholderText("Atmak istediğin mail sayısını gir. Çok fazla girmeni önermem!")
        int_only = QIntValidator()
        self.numberEmailInput.setValidator(int_only)
        self.numberEmailInput.textChanged.connect(self.sendMailButtonText)

        # ADD FILE BUTTON
        fileButton = QPushButton("Dosya Ekle")
        fileButton.clicked.connect(self.fileButtonClicked)

        # SEND BUTTON
        self.sendMailButton = QPushButton(f"0 Tane Mail Yolla")
        self.sendMailButton.clicked.connect(self.start)

        # SETTING LAYOUT
        layout.addWidget(title, 0, 0, 1, 4, alignment=Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(emailLabel, 1, 0, 1, 1)
        layout.addWidget(self.emailInput, 1, 1, 1, 2)
        layout.addWidget(ccEmailLabel, 2, 0, 1, 1)
        layout.addWidget(self.ccEmailInput, 2, 1, 1, 2)
        layout.addWidget(appPasswordLabel, 3, 0, 1, 1)
        layout.addWidget(self.appPasswordInput, 3, 1, 1, 2)
        layout.addWidget(numberEmailLabel, 4, 0, 1, 1)
        layout.addWidget(self.numberEmailInput, 4, 1, 1, 2)
        layout.addWidget(fileButton, 2, 3, 2, 1, alignment=Qt.AlignmentFlag.AlignCenter)
        layout.addWidget(self.sendMailButton, 5, 0, 1, 4, alignment=Qt.AlignmentFlag.AlignCenter)

        centerWidget = QWidget()
        centerWidget.setLayout(layout)
        self.setCentralWidget(centerWidget)

    # CHANGES THE SEND BUTTON TEXT
    def sendMailButtonText(self, newText):
        self.sendMailButton.setText(f"{newText} Tane Mail Yolla!")

    # GET .CSV FILE
    def fileButtonClicked(self):
        dlg = QFileDialog()
        dlg.setNameFilters(["*.xlsx"])
        dialogSuccessful = dlg.exec()

        if dialogSuccessful == 1:
            self.selectedFile = dlg.selectedFiles()

    # MAILSENDER STARTER 
    def start(self):

        # INIT ESSENTIALS 
        senderEmail = self.emailInput.text()
        ccEmail = self.ccEmailInput.text()
        appPassword = self.appPasswordInput.text()
        numberEmail = self.numberEmailInput.text()

        # RECEIVE MAIL INFORMATION
        excel_file = pd.read_excel(self.selectedFile[0])
        emails = excel_file["Mail Adresi"]
        company = excel_file["Marka Adı"]
        names = excel_file["Kişi Adı"]

        for index, email in enumerate(emails):
            body = f"""Sayın {names[index]},
                  Ben Cağaloğlu Anadolu Lisesinden X kişisi. 
                  ... 
                  Bu yüzden siz {company[index]} ile iletişime geçiyoruz.
                  Bu bir test yazısıdır. Yani yukarıda yazılanlara itibar etmeyiniz."""
            
            mailSender = MailSender(senderEmail, email, "Test", body, appPassword)
            mailSender.send_email()


app = QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()