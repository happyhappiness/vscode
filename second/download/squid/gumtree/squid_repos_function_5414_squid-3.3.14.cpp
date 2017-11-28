static void
mcast_encode(unsigned int *ibuf, size_t isize, const unsigned int *key)
{
    unsigned int y;
    unsigned int z;
    unsigned int sum;
    const unsigned int delta = 0x9e3779b9;
    unsigned int n = 32;
    const unsigned int k0 = htonl(key[0]);
    const unsigned int k1 = htonl(key[1]);
    const unsigned int k2 = htonl(key[2]);
    const unsigned int k3 = htonl(key[3]);
    int i;

    for (i = 0; i < isize; i += 2) {
        y = htonl(ibuf[i]);
        z = htonl(ibuf[i + 1]);
        sum = 0;

        for (n = 32; n; --n) {
            sum += delta;
            y += (z << 4) + (k0 ^ z) + (sum ^ (z >> 5)) + k1;
            z += (y << 4) + (k2 ^ y) + (sum ^ (y >> 5)) + k3;
        }

        ibuf[i] = htonl(y);
        ibuf[i + 1] = htonl(z);
    }
}