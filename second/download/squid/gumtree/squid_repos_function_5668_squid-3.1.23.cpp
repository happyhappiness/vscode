unsigned int
hash_string(const void *data, unsigned int size)
{
    const char *s = data;
    unsigned int n = 0;
    unsigned int j = 0;
    unsigned int i = 0;
    while (*s) {
        j++;
        n ^= 271 * (unsigned) *s++;
    }
    i = n ^ (j * 271);
    return i % size;
}