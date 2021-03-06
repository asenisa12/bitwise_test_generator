import HTML
import sys
import pdfkit

def main():
	floder = sys.argv[1]
	name="<p align='center'> Test Number: "+floder[4:] +"<p>"
	t = HTML.Table(["",""])
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
	
	result = open(floder+"/result.txt",'r')
	tr = HTML.Table(header_row=["task number","result"])
	strr = ["",""]
	for x in range (1,13):
		line = str(result.readline())
		c=2
		if x>9:
			c=3
		strr[0] = line[:c]
		strr[1] = line[c:]
		tr.rows.append(strr)
		strr = ["",""]


	s = str(t)
	htmlcode= name + s[:6] + ' align="center"' + s[6:]
	htmlcodeRes =name+ str(tr)

	f = open(floder+"/test"+str(floder[4:])+".html","w")
	f.write(htmlcode)
	r = open(floder+"/result"+str(floder[4:])+".html","w")
	r.write(htmlcodeRes)
	f.close()
	r.close()

	pdfkit.from_string(htmlcode, floder+"/test"+str(floder[4:])+".pdf")
	pdfkit.from_string(htmlcodeRes, floder+"/result"+str(floder[4:])+".pdf")



if __name__=="__main__":
	main()	