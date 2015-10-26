from __future__ import division
from math import pi, log10, floor

def scaleSigFigs(x, n):
    # Scales x by factors of 10 such that n digits are left of the decimal place
    # Example: getSigFigs(12.345, 3) returns (123.45, 2.0)
    # Useful when looking up 'prefered values such as in the resistor E-series'
    
    # retuns (scaled significand, scaled exponent)
    
    exp = floor(log10(x))
    return x*10**(-1*exp+n-1), exp-n+1

def getEVal(x, tol):
    tols = {
        0.5:{'steps':192, 'n':3},
        1:{'steps':96, 'n':3},
        2:{'steps':48, 'n':3},
        5:{'steps':24, 'n':2},
        10:{'steps':12, 'n':2},
        20:{'steps':6, 'n':2}
        }
    if tol not in tols:
        print('Warning: Using default tolerance of 1%')
    steps = tols.get(tol, tols[1])['steps']
    n = tols.get(tol, tols[1])['n']
    sig, exp = scaleSigFigs(x, n)
    return 10**exp*min(getRenardNumbers(steps, n), key=lambda v:abs(v-sig))

def getRenardNumbers(steps, n):
    # Return 'steps', n-digit RenardNumbers
    return [int(round(10**(i/steps + n-1))) for i in range(steps)]


def valToSI(val, n = 3, unit = ''):
    units = {
        'ohm':u'\u2126',
        'F':'F',
        'farad':'F'
        }
    prefixes = {-12:'p', -9:'n', -6:'u', -3:'u',
                0:'',
                3:'k', 6:'M', 9:'G', 12:'T'
                }
    
    s, e = scaleSigFigs(val, 1)
    s = str(round(s,n)*10**(e%3))
    return '%s %s%s' % (s, prefixes[e - e%3], units.get(unit, ''))

tol = 1
F = 7.15e6
B = 300e3
H = 20


Q = F/B

R1 = 10e3
R3 = 2*R1*H
R2 = R3 / (4*Q**2 - 2*H)
C = Q/(pi*F*R3)

print("Calculated:  R1 = %.3e, R2 = %.3e, R3 = %.3e" % (R1, R2, R3))
print("Calculated:  C = %.3e" % (C))
Cs = getEVal(C, tol)

print("Chosen (%d%%):  C = %s" % (tol, valToSI(Cs, unit = 'F')))

R3 = Q/(pi*F*C)
R1 = R3/(2*H)
R2 = R3 / (4*Q**2 - 2*H)

print ("Calculated:  R1 = %.3e, R2 = %.3e, R3 = %.3e" % (R1, R2, R3))
R3 = getEVal(Q/(pi*F*C), tol)
R1 = getEVal(R3/(2*H), tol)
R2 = getEVal(R3 / (4*Q**2 - 2*H), tol)
print ("Chosen (%d%%):  R1 = %s, R2 = %s, R3 = %s" % (tol, valToSI(R1, unit = 'ohm'), valToSI(R2, unit = 'ohm'), valToSI(R3, unit = 'ohm')))


