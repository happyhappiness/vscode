unsigned int
storeKeyHashHash(const void *key, unsigned int n)
{
    /* note, n must be a power of 2! */
    const unsigned char *digest = (const unsigned char *)key;
    unsigned int i = digest[0]
                     | digest[1] << 8
                     | digest[2] << 16
                     | digest[3] << 24;
    return (i & (--n));
}