# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    email.py                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 14:25:37 by irhett            #+#    #+#              #
#    Updated: 2017/04/14 14:52:54 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import smtplib											# AB
from email.MIMEMUltipart import MIMEMultipart			# B
from email.MIMEText import MIMEText						# B

fromaddr = "MY ADDR"									# AB
toaddr = "TARGET ADDR"									# B
msg = MIMEMultipart()									# B
msg['From'] = fromaddr									# B
msg['To'] = toaddr										# B
msg['Subject'] = "Subject"								# B

body = "Message Body"									# B
msg.attach(MIMEText(body, 'plain'))						# B


server = smtplib.SMTP('???.gmail.co?', 587)				# AB
server.starttls()										# AB
server.login(fromaddr, "YOUR PASSWORD")					# AB

text = msg.as_string()									# B

msg_a = "YOUR MESSAGE!"									# A

server.sendmail("YOUR EMAIL", "EMAIL TARGET", msg_a)	# A
server.sendmail("YOUR EMAIL", "EMAIL TARGET", text)		# B

server.quit()											# AB
