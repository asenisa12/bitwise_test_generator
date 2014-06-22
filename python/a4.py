#!/usr/bin/env python

import copy, sys
from pyPdf import PdfFileWriter, PdfFileReader

op = PdfFileWriter()

op.addBlankPage(210,297)
ops = file("document-output.pdf", "wb")  
op.write(ops)  
ops.close() 


