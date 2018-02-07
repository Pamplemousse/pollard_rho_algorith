def gen_group (size_modulus, size_order):
    (p, q, alpha) = gen_modulus (size_modulus, size_order)
    f = 2
    while true:
        if pow(f, alpha, p) != 1:
            return (p, q, f)
        f += 1

def gen_modulus (size_modulus, size_order):
    n = size_modulus - size_order
    q = gen_order(size_order)
    while true:
        alpha = sage.rings.integer.Integer(randint(10^(n-1), 10^n - 1))
        if (alpha * q + 1).is_prime():
            return (alpha * q + 1, q, alpha)

def gen_order (size_order):
    while true:
        q = sage.rings.integer.Integer(randint(10^(size_order - 1), \
            10^size_order - 1))
        if q.is_prime():
            return q
