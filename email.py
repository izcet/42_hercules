# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    email.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 14:25:37 by irhett            #+#    #+#              #
#    Updated: 2017/04/14 15:12:57 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import smtplib											# AB
from email.MIMEMUltipart import MIMEMultipart			# B
from email.MIMEText import MIMEText						# B

fromaddr = "apikey"										# AB
key = "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"
toaddr = "nartnetworks@grr.la"							# B
msg = MIMEMultipart()									# B
msg['From'] = fromaddr									# B
msg['To'] = toaddr										# B
msg['Subject'] = "Test Message"							# B

body = "Message Body"									# B
msg.attach(MIMEText(body, 'plain'))						# B

server = smtplib.SMTP('smtp.sendgrid.net', 587)			# AB
server.starttls()										# AB
server.login(fromaddr, key)								# AB

text = msg.as_string()									# B

#msg_a = "YOUR MESSAGE!"								# A

#server.sendmail("YOUR EMAIL", "EMAIL TARGET", msg_a)	# A
server.sendmail("user@website.co", toaddr, text)		# B

server.quit()											# AB
