import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

class MailSender:
    def __init__(self, senderEmail, receiverEmail, subject, body, password):
        self.senderEmail = senderEmail
        self.receiverEmail = receiverEmail
        self.subject = subject
        self.body = body
        self.password = password

    def send_email(self):
        msg = MIMEMultipart()
        msg['From'] = self.senderEmail
        msg['To'] = self.receiverEmail
        msg['Subject'] = self.subject
        msg.attach(MIMEText(self.body, 'plain'))

        try: 
            server = smtplib.SMTP('smtp.gmail.com', 587)
            server.starttls()
            server.login(self.senderEmail, self.password)

            text = msg.as_string()
            server.sendmail(self.senderEmail, self.receiverEmail, text)
            print("E-Posta başarılı")

            server.quit()

        except Exception as e:
            print(f"Hata: {e}")