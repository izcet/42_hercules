# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    cattle.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irhett <irhett@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/22 19:56:55 by irhett            #+#    #+#              #
#    Updated: 2017/04/24 19:41:44 by irhett           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from urlparse import urlparse
from threading import Thread
import httplib, sys, getopt, time, array

num_threads = 0
verbosity = 0
url = ""
num = 0
requests_sent = 0

totalTime = 0.0
codes = array.array('I', (0 for i in range(0,600)))

def dowork(user):
	global verbosity
	global num
	global num_threads
	v = verbosity
	user += 1
	u = str(user)
	if (v > 0):
		print("User number " + u + " starting.")
	start = time.time()
	for a in range(num):
		n = str(a)
		latency = getStatus(u, n, v)
		if (v > 2):
			print("Latency is " + str(latency))
	end = time.time()
	if (v > 0):
		print("User number " + u + " stopping.")
	if (v > 1):
		print("User " + u + " took " + str(end - start) + " seconds.")
	num_threads -= 1

def getStatus(user, num, verbosity):
	global requests_sent
	try:
		ourl = urlparse(url)
		conn = httplib.HTTPConnection(ourl.netloc)
		if (verbosity > 2):
			print("User " + user + "request number " + num + " sent.")
		start = time.time()
		conn.request("HEAD", ourl.path)
		res = conn.getresponse().status
		end = time.time()
		if (verbosity > 2):
			print("User " + user + " request " + num + " returned " + str(res))
		codes[res] += 1
		requests_sent += 1
		return (end - start)
	except StandardError:
		return -1

def wait_until():
	try:
		global num_threads
		while (num_threads > 0):
			time.sleep(0.001)
		return False
	except KeyboardInterrupt:
		return False

def main(name, argv):
	usage = name + ' -n <num users> -r <num requests> -u <url>'
	users = 0
	global verbosity
	global num
	global url
	global num_threads
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
			verbosity += 1
		else:
			print(usage)
			sys.exit(2)
	num_threads = users
	start = time.time()
	for i in range(users):
		t = Thread(target=dowork, args=(i,))
		t.start()
	wait_until()
	end = time.time()
	if (verbosity > 0):
		print ""
	print("Total number of requests sent: " + str(requests_sent))
	print("Total time elapsed was " + str(end - start) + " seconds.")
	for index, value in enumerate(codes):
		if (value > 0):
			i = str(index)
			v = str(value)
			print("HTTP Status code " + i + " was returned " + v + " times.")
	exit(0)

if __name__ == "__main__":
	main(sys.argv[0], sys.argv[1:])
