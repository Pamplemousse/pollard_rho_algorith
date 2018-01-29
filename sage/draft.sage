import pdb


def rho_table(alpha=2, beta=228, modulus=383, order=191):
    x = [1]
    a = [0]
    b = [0]

    for i in range(14):
        (next_x, next_a, next_b) = f(x[i], a[i], b[i],
                                     alpha, beta, modulus, order)
        x.append(next_x)
        a.append(next_a)
        b.append(next_b)

    print x
    print a
    print b

    # print("i\txi\tai\tbi\tx2i\ta2i\tb2i\n")
    # for i in range(1, 15):
    #     print str(i) + "\t" + str(x[i]) + "\t" + str(a[i]) + "\t" + str(b[i]) \
    #       + "\t" + str(x[2 * i]) + "\t" + str(a[2 * i]) + "\t" + str(b[2 * i])


def f(xi, ai, bi, alpha, beta, modulus, order):
    if xi % 3 == 1:
        next_x = (beta * xi) % modulus
        next_a = ai
        next_b = (bi + 1) % order
    elif xi % 3 == 0:
        next_x = (xi * xi) % modulus
        next_a = (2 * ai) % order
        next_b = (2 * bi) % order
    else:
        next_x = (alpha * xi) % modulus
        next_a = (ai + 1) % order
        next_b = bi

    return (next_x, next_a, next_b)
