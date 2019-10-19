import subprocess

def check(expr, result):
    out = subprocess.run(['./LinearAllocator', expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('Error.\n{0} \nExpected: {1} \ngot: {2}\n'.format(expr, result, out.stdout))
    else:
        print('Correct.\n{0} \nExpected: {1} \ngot: {2}\n'.format(expr, result, out.stdout))

check("100 10 60 80 r 90", "allocated allocated out of memory allocated ")
check("10 1000 1 9 1 r 1", "out of memory allocated allocated out of memory allocated ")
