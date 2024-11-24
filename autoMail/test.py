import pandas as pd 
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

excelPath = r"c:\Users\user\Desktop\Kitap1.xlsx"

class MailSender:
    def __init__(self, filePath, numberEmails, senderEmail):
        self.filePath = filePath
        self.numberEmails = numberEmails
        self.senderEmail = senderEmail
        
        self.dataset = pd.read_excel(self.filePath)
        self.columnCount = len(self.dataset.columns)


    def getInformation(self):
        index = 0 


        if self.columnCount != 2 and self.columnCount != 3:
            print("Dataseti Düzenleyiniz!")
            print(self.columnCount)

        else:
            emails = list()
            names = list()
            
            if self.columnCount == 2: 
                
                for _, row in self.dataset.iterrows():
                    emails.append(row["Email Adresi"])
                    names.append(row["İsim Soyisim"])
                    index += 1

                    if index == self.numberEmails:
                        break

            
            if self.columnCount == 3:
                for _, row in self.dataset.iterrows():
                    if pd.isna(row["Mail Atıldı mı?"]):
                        emails.append(row["Email Adresi"])
                        names.append(row["İsim Soyisim"])
                        index += 1

                    elif not pd.isna(row["Mail Atıldı mı?"]):
                        continue

                    if index == self.numberEmails:
                        break

        return emails, names
        

    def sendMails(self, receiver_emails, receiver_names, isSendedList, subject, password):
        pass
        # for i in range(len(receiver_emails)):
        #     msg = MIMEMultipart()
        #     msg['From'] = sender_email
        #     msg['To'] = receiver_emails[i]
        #     msg['Subject'] = subject

        #     # Mesaj gövdesini ekle
        #     body = f"""
        #            Merhaba {receiver_names[i]}!
        #            Bu bir test yazısıdır. 
        #            Bu yazıya ihbar etmeyiniz"""
        #     msg.attach(MIMEText(body, 'plain'))

        #     try:
        #         # SMTP sunucusuna bağlan ve giriş yap
        #         server = smtplib.SMTP('smtp.gmail.com', 587)
        #         server.starttls()  # Bağlantıyı güvenli hale getir
        #         server.login(sender_email, password)

        #         # E-postayı gönder
        #         text = msg.as_string()
        #         # server.sendmail(sender_email, receiver_emails[i], text)
        #         print("E-posta başarıyla gönderildi!")

        #         # Sunucu bağlantısını kapat
        #         server.quit()

        #     except Exception as e:
        #         print(f"E-posta gönderiminde bir hata oluştu: {e}")


    def changeExcelFile(self, sendedEmails:list):   
        
        for index, row in self.dataset.iterrows():
            if row["Email Adresi"] in sendedEmails:
                self.dataset.iloc[index, 2] = 1
            else:
                continue

mailSender = MailSender(excelPath, 1, "utkuevkaya@gmail.com")
emails, names = mailSender.getInformation()
mailSender.changeExcelFile(emails)
print(mailSender.dataset)