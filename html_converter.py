import HTML
import sys

def main():
	floder = sys.argv[1]

	t = HTML.Table(["","",""])
	test=open(floder+"/test.txt",'r')
	count =0
	strs = ["",""]

	for x in range(1,76):
		line=test.readline()
		
		if line == "\n":
			if count==0:
				count =1;
			else:
				count=0
				t.rows.append(strs)
				strs = ["",""]

		strs[count]+=line+'<br> '
	
	
	htmlcode = str(t)
	f = open(floder+"/test.html","w")
	f.write(htmlcode)

if __name__=="__main__":
	main()	