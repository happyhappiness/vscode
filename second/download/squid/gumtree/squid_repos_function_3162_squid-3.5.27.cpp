int
storeKeyHashBuckets(int nbuckets)
{
    int n = 0x2000;

    while (n < nbuckets)
        n <<= 1;

    return n;
}