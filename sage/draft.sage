import pdb


def rho_table(alpha=2, beta=228, modulus=383, order=191):
    x = [1]
    a = [0]
    b = [0]

    for i in range(30):
        next_x = f(x[i], alpha, beta, modulus)
        x.append(next_x)

        next_a = fa(a[i], x[i], order)
        a.append(next_a)

        next_b = fb(b[i], x[i], order)
        b.append(next_b)


    print("i\txi\tai\tbi\tx2i\ta2i\tb2i\n")
    for i in range(1, 15):
        print str(i) + "\t" + str(x[i]) + "\t" + str(a[i]) + "\t" + str(b[i]) \
          + "\t" + str(x[2 * i]) + "\t" + str(a[2 * i]) + "\t" + str(b[2 * i])


def f(xi, alpha, beta, modulus):
    if xi % 3 == 1:
        result = (beta * xi) % modulus
    elif xi % 3 == 0:
        result = (xi * xi) % modulus
    else:
        result = (alpha * xi) % modulus

    return result


def fa(ai, xi, modulus):
    if xi % 3 == 1:
        result = ai
    elif xi % 3 == 0:
        result = (2 * ai) % modulus
    else:
        result = (ai + 1) % modulus

    return result


def fb(bi, xi, modulus):
    if xi % 3 == 1:
        result = (bi + 1) % modulus
    elif xi % 3 == 0:
        result = (2 * bi) % modulus
    else:
        result = bi

    return result
