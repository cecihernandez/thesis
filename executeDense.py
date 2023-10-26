#!/usr/bin/python

import sys,os

if len(sys.argv)!=6:
  print "usage: "+sys.argv[0]+" <graphin> <iter> <output> <P> <ES>"
  sys.exit(0)

res=os.system("./dsextract/vnmextract "+sys.argv[1]+ " 1 1 "+ sys.argv[2] + " " + sys.argv[3] + " "+sys.argv[4]+" "+ sys.argv[5])
print "./dsextract/vnmextract done: "+str(res)

if res!=0:
  print "./dsextract/vnmextract failed, aborting"
  sys.exit(1)

#print "Removing temporary files"
#for ext in ["rp","dict","ptr"]:
#  res=os.system("rm -f "+sys.argv[1]+"."+ext)
