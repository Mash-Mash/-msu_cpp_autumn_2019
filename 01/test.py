import subprocess

def check(expr, result):
    out = subprocess.run(['./calculator', expr], stdout=subprocess.PIPE)
    if out.stdout.decode('ascii') != result:
        print('Error {0} != {1}, got {2}'.format(expr, result, out.stdout))
    else:
        print('Correct {0} == {1}, got {2}'.format(expr, result, out.stdout))

check("1", '1')
check("-1", '-1')
check("1 +2", '3')
check("1- 2", '-1')
check(" -1 +  -2 ", '-3')
check(" 1 *  -3 +21 /7", '0')
check("2/2/2", '0')
check("1-2+3-4", '-2')
check("2 + 1", '3')
check("1/0","Error: division by zero")

