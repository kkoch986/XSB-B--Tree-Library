################################################################################
# Generate testfiles for main memory updates                                   
#
# Generate three files as described in python/ directory
################################################################################
import sys

class TestFile:
    def __init__(self, _upperBound, _sys, _predicateName):
        self.upperBound = _upperBound
        self.sys = _sys
        self.predicateName = _predicateName

    def Generate(self):
        _filename = 'upper' + str(self.upperBound) + '_pattern'
        if sys == 'xsb':
            filename_suffix = '.P'
        elif sys == 'yap':
            filename_suffix = '.pl'
        elif sys == 'swi':
            filename_suffix = '.pl'
        elif sys == 'jess':
            filename_suffix = '.jess'
        elif sys == 'dlv':
            filename_suffix = '.dlv'
        elif sys == 'owlim':
            filename_suffix = '.owlim'
        else:
            print 'system: ', sys, ' is not known'
        _filename1 = _filename + '(1,i)_' + self.sys + filename_suffix
        _filename2 = _filename + '(i,1)_' + self.sys + filename_suffix
        _filename3 = _filename + '(i,i)_' + self.sys + filename_suffix
        f1 = open(_filename1, 'w')
        f2 = open(_filename2, 'w')
        f3 = open(_filename3, 'w')
        for i in range(self.upperBound):
            if sys in ['xsb', 'yap', 'dlv', 'swi']:
                f1.write(self.predicateName+'(1,'+str(i+1)+').\n')
                f2.write(self.predicateName+'('+str(i+1)+',1).\n')
                f3.write(self.predicateName+'('+str(i+1)+','+str(i+1)+').\n')
            elif sys == 'jess':
                f1.write('('+self.predicateName+' 1 '+str(i+1)+')\n')
                f2.write('('+self.predicateName+' '+str(i+1)+' 1)\n')
                f3.write('('+self.predicateName+' '+str(i+1)+' '+str(i+1)+')\n')
            elif sys == 'owlim':
                f1.write(self.predicateName + '\n' + '1\n' + str(i+1) + '\n')
                f2.write(self.predicateName + '\n' + str(i+1) + '\n' + '1\n')
                f3.write(self.predicateName + '\n' + str(i+1) + '\n' + str(i+1) + '\n')
            else:
                print 'system: ', sys, ' is not known'
                sys.exit()
        f1.close()
        f2.close()
        f3.close()
        print 'generated: ', _filename1
        print 'generated: ', _filename2
        print 'generated: ', _filename3

################################################################################

# get the system List
sysList = []
for arg in sys.argv[1:]:
    sysList.append(arg)

if len(sysList) == 0:
    sys.exit()

# test sizes
sizes = [50000, 100000, 250000, 500000, 1000000]

# generated data files
for sys in sysList:
    for i in sizes:
        testFile = TestFile(i, sys, "p")
        testFile.Generate()
