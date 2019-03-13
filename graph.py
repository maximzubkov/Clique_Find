with open("graph_input.txt", "r") as i:
	with open("graph.txt", "w") as o:
		txt = i.read().split(",")
		s = ""
		for w in txt:
			s += str(w)
		o.write(s)
