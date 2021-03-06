# Retourne un triplet (module, ordre, générateur)
def gen_group (size_modulus, size_order):
    (p, q, u) = gen_modulus (size_modulus, size_order)
    pre_g = 2
    while true:
        g = int(pow(pre_g, u, p))
        if g != 1:
            return (p, q, g)
        pre_g += 1

# Construction de p tel que q | (p - 1)
#                       <=> p = uq + 1
def gen_modulus (size_modulus, size_order):
    n = size_modulus - size_order
    q = gen_order(size_order)
    while true:
        u = sage.rings.integer.Integer(randint(2^(n-1), 2^n - 1))
        if (u * q + 1).is_prime():
            return (u * q + 1, q, u)

# Générer q premier de "size_order" bits
def gen_order (size_order):
    while true:
        q = sage.rings.integer.Integer(
            randint(2^(size_order - 1), 2^size_order - 1)
        )
        if q.is_prime():
            return q

# Générer un ensemble de "p q g h x" tels que g^x = h mod p
def gen_data(p, q, g):
    s = ""
    for _ in range(100):
        x = randrange(1, q)
        h = int(pow(g, x, p))
        s = s + '{:b} {:b} {:b} {:b} {:b}\n'.format(p, q, g, h, x)
    return s

# Générer un fichier contenant un ensemble de test
def gen_test_inputs():
    f = open('inputs.txt','w')
    for size_q in [5..55]:
        (p, q, g) = gen_group(size_q+10, size_q)
        f.write(gen_data(p, q, g))
    f.close()
