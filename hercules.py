# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hercules.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 14:25:37 by irhett            #+#    #+#              #
#    Updated: 2017/04/14 19:11:52 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys, getopt
import smtplib
import os.path
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText
from email.MIMEBase import MIMEBase
from email import encoders

def main(argv):
	message_subject = ""
	message_body = ""
	message_recipients = []
	message_attachments = []
	my_dir = os.path.dirname(__file__)
	fromaddr = "hercules@amazon.com"
	ky = "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"
	try:
		opts, args = getopt.getopt(argv,"hs:m:r:a:")
	except getopt.GetoptError:
		print 'hercules.py -s <subjectfile> -m <messagefile> -r <intra_names> [ -e <email> ] [ -a <attachment> ] ...'
		sys.exit(2)
	for opt, arg in opts:
		if (opt == '-h'):
			print 'hercules.py -s <subjectfile> -m <messagefile> -r <intra_names> [ -e <email> ] [ -a <attachment> ] ...'
			sys.exit()
		if (opt == '-s'):
			subject_file = open(os.path.join(my_dir, arg), "r")
			message_subject = subject_file.read()
			subject_file.close()
		elif (opt == '-m'):
			body_file = open(os.path.join(my_dir, arg), "r")
			message_body = body_file.read()
			body_file.close()
		elif (opt == '-r'):
			recipient_file = open(os.path.join(my_dir, arg), "r")
			for line in recipient_file:
				message_recipients.append(line[:-1] + "@student.42.us.org")
			recipient_file.close()
		elif (opt == '-e'):
			message_recipients.append(arg)
		elif (opt == '-a'):
			message_attachments.append(os.path.join(my_dir, arg))
		else:
			print 'hercules.py -s <subjectfile> -m <messagefile> -r <intra_names> [ -e <email> ] [ -a <attachment> ] ...'
			sys.exit(2)
	msg = MIMEMultipart()
	msg['From'] = fromaddr
	print("Message Subject:")
	print(message_subject)
	msg['Subject'] = message_subject 
	print("Message Body:")
	print(message_body)
	msg.attach(MIMEText(message_body, 'html'))
	for filen in message_attachments:
		print("Attaching File: " + filen)
		attachment = open(filen, "rb")
		part = MIMEBase('application', 'octet-stream')
		part.set_payload((attachment).read())
		encoders.encode_base64(part)
		part.add_header('Content-Disposition', "attachment; filename= %s" % filen)
		msg.attach(part)
	server = smtplib.SMTP('smtp.sendgrid.net', 587)
	server.starttls()
	server.login('apikey', ky)
	for user in message_recipients:
		toaddr = user
		msg['To'] = toaddr
		text = msg.as_string()
		server.sendmail(fromaddr, toaddr, text)
		print("Sending mail to: " + toaddr)
	server.quit()

if __name__ == "__main__":
	main(sys.argv[1:])
