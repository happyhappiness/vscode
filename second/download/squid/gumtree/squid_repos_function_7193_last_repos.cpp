static
unsigned int
hash_key(const unsigned char *data, unsigned int len, unsigned int hashSize)
{
    unsigned int n;
    unsigned int j;
    for (j = 0, n = 0; j < len; j++ ) {
        n ^= 271 * *data;
        ++data;
    }
    return (n ^ (j * 271)) % hashSize;
}