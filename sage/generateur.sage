# Retourne un triplet (module, ordre, générateur)
def gen_group (size_modulus, size_order):
    (p, q, u) = gen_modulus (size_modulus, size_order)
    pre_alpha = 2
    while true:
        alpha = pow(pre_alpha, u, p)
        if alpha != 1:
            return (p, q, alpha)
        pre_alpha += 1

# Construction de p tel que q | (p - 1)
#                       <=> p = uq + 1
def gen_modulus (size_modulus, size_order):
    n = size_modulus - size_order
    q = gen_order(size_order)
    while true:
        u = sage.rings.integer.Integer(randint(10^(n-1), 10^n - 1))
        if (u * q + 1).is_prime():
            return (u * q + 1, q, u)

# Générer q premier de longueur "size"
def gen_order (size_order):
    while true:
        q = sage.rings.integer.Integer(
            randint(10^(size_order - 1), 10^size_order - 1)
        )
        if q.is_prime():
            return q

# Générer un ensemble de "p q g h x" tels que g^x = h mod p 
def gen_data():
    p = 46795003
    q = 7799167
    g = 64

    for _ in range(20):
        x = randrange(1,100)
        h = pow(g, x, p)
        print '{} {} {} {} {}'.format(p, q, g, h, x)
