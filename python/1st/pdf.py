#!/usr/bin/env python
import copy, sys
from pyPdf import PdfFileWriter, PdfFileReader

op = PdfFileWriter() 

op.addBlankPage(200,200)
ops = file("document-output.pdf", "wb")  
op.write(ops)  
ops.close() 
