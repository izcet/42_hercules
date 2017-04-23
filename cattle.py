# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cattle.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/22 19:56:55 by irhett            #+#    #+#              #
#    Updated: 2017/04/22 22:22:37 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from urlparse import urlparse
from threading import Thread
import httplib, sys, getopt
from Queue import Queue

def doPrint(status, url):
#	iif (status != -1):
#		print url, str(status)
#	else:
#		print url
	print ""

def dowork(url, num, q):
	for _ in range(num):
		status, url = getStatus(url)
		doPrint(status, url)
#		q.task_done()

def getStatus(url):
	try:
		ourl = urlparse(url)
		conn = httplib.HTTPConnection(ourl.netloc)
		print("Sending response to " + url)
		conn.request("HEAD", ourl.path)
		res = conn.getresponse().status
		print("Response is " + str(res))
		return res, url
	except StandardError:
		return -1, url

def main(name, argv):
	usage = name + ' -n <num users> -r <num requests> -u <url>'
	users = 0
	num = 0
	url = ""
	verbosity = 0
	try:
		opts, args = getopt.getopt(argv, "hn:r:u:v")
	except getopt.GetoptError:
		print(usage)
		sys.exit(2)
	for opt, arg in opts:
		if (opt == '-h'):
			print(usage)
			sys.exit()
		elif (opt == '-n'):
			users = int(arg)
		elif (opt == '-r'):
			num = int(arg)
		elif (opt == '-u'):
			url = arg
		elif (opt == '-v'):
			verbosity++
		else:
			print(usage)
			sys.exit(2)
	q = Queue(users * 2)
	for _ in range(users):
		t = Thread(target=dowork, args=(url, num, q))
		t.start()
	q.join()

if __name__ == "__main__":
	main(sys.argv[0], sys.argv[1:])
