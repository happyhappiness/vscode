static unsigned int
fsHash(const void *key, unsigned int n)
{
    /* note, n must be a power of 2! */
    const int *k = (const int *)key;
    return (*k & (--n));
}