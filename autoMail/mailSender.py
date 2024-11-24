import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def send_email(sender_email, receiver_email, subject, body, password):
    # Mesaj oluştur
    msg = MIMEMultipart()
    msg['From'] = sender_email
    msg['To'] = receiver_email
    msg['Subject'] = subject

    # Mesaj gövdesini ekle
    msg.attach(MIMEText(body, 'plain'))

    try:
        # SMTP sunucusuna bağlan ve giriş yap
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()  # Bağlantıyı güvenli hale getir
        server.login(sender_email, password)

        # E-postayı gönder
        text = msg.as_string()
        server.sendmail(sender_email, receiver_email, text)
        print("E-posta başarıyla gönderildi!")

        # Sunucu bağlantısını kapat
        server.quit()

    except Exception as e:
        print(f"E-posta gönderiminde bir hata oluştu: {e}")

if __name__ == "__main__":
    sender = "utkuevkaya@gmail.com"
    receiver = "arda.evkaya.ub.10@istek.k12.tr"
    subject = "Test Mail"
    body = "This is a test email from Python."
    password = "wdye rqmf hjsk bbuk"

    send_email(sender, receiver, subject, body, password)



#TODO
# import smtplib 
# from email.mime.text import MIMEText
# from email.mime.multipart import MIMEMultipart

# class emailSender:
#     def __init__(self, sender, receivers, password, subject, body):
#         pass
