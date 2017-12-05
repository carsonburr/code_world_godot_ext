import cw
n = 0

def run():
	global n
	if n is None:
		n = 0
		print("init")
	if n == 0:
		cw.test("u")
	elif n == 1:
		cw.test("d")
	elif n == 2:
		cw.test("l")
	else:
		cw.test("r")
	n = n + 1
