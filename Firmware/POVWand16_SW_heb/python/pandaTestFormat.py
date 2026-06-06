
import argparse


# command arguments
parser = argparse.ArgumentParser(description='Hebrew')
parser.add_argument('-s','--string', help='enter hebrew string', action='store',default= '', required=True)
args = parser.parse_args()

if args.string != '':
    hebString = args.string.decode('iso8859_8')
    print (hebString)
    output = ''
    for x in hebString:
        output =  chr(ord(x)-1391) + output
    print(output)
