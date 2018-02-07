def rho_solve(alpha=2, beta=228, modulus=383, order=191):
    table = rho_table(alpha, beta, modulus, order)
    print_table(table)

    a = table[1][-1]
    b = table[2][-1]
    A = table[4][-1]
    B = table[5][-1]

    solution = solve(a, b, A, B, order)
    print "\nlog_" + str(alpha) + "(" + str(beta) + ") = " \
      + str(solution) + " mod " + str(order)


def rho_table(alpha, beta, modulus, order):
    x = [1]; X = [1]
    a = [0]; A = [0]
    b = [0]; B = [0]

    for i in range(order):
        (next_x, next_a, next_b) = f(x[i], a[i], b[i],
                                     alpha, beta, modulus, order)

        (next_X, next_A, next_B) = f(X[i], A[i], B[i],
                                     alpha, beta, modulus, order)
        (next_X, next_A, next_B) = f(next_X, next_A, next_B,
                                     alpha, beta, modulus, order)

        x.append(next_x)
        a.append(next_a)
        b.append(next_b)
        X.append(next_X)
        A.append(next_A)
        B.append(next_B)

        if (next_x == next_X):
            break;

    return (x, a, b, X, A, B)



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


def solve(ai, bi, a2i, b2i, order):
    return (a2i - ai) * (inverse_mod((bi - b2i), order)) % order


def print_table(table):
    (x, a, b, X, A, B) = table

    print("i\txi\tai\tbi\tx2i\ta2i\tb2i\n")
    for i in range(len(x)):
        print str(i) + "\t" + str(x[i]) + "\t" + str(a[i]) + "\t" + str(b[i]) \
          + "\t" + str(X[i]) + "\t" + str(A[i]) + "\t" + str(B[i])
