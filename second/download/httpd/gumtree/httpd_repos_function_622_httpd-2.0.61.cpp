static unsigned int hash(const unsigned char *key,
                         const unsigned int length,
                         const unsigned int init_val)
{
    const unsigned char *key_p = key;
    unsigned int a, b, c, len;

    /* set up the internal state */
    a = 0x9e3779b9;             /* the golden ratio; an arbitrary value */
    b = 0x9e3779b9;
    c = init_val;               /* the previous hash value */

    /* handle most of the key */
    for (len = length; len >= 12; len -= 12) {
        a += (key_p[0]
              + ((unsigned long) key_p[1] << 8)
              + ((unsigned long) key_p[2] << 16)
              + ((unsigned long) key_p[3] << 24));
        b += (key_p[4]
              + ((unsigned long) key_p[5] << 8)
              + ((unsigned long) key_p[6] << 16)
              + ((unsigned long) key_p[7] << 24));
        c += (key_p[8]
              + ((unsigned long) key_p[9] << 8)
              + ((unsigned long) key_p[10] << 16)
              + ((unsigned long) key_p[11] << 24));
        HASH_MIX(a, b, c);
        key_p += 12;
    }

    c += length;

    /* all the case statements fall through to the next */
    switch (len) {
    case 11:
        c += ((unsigned long) key_p[10] << 24);
    case 10:
        c += ((unsigned long) key_p[9] << 16);
    case 9:
        c += ((unsigned long) key_p[8] << 8);
        /* the first byte of c is reserved for the length */
    case 8:
        b += ((unsigned long) key_p[7] << 24);
    case 7:
        b += ((unsigned long) key_p[6] << 16);
    case 6:
        b += ((unsigned long) key_p[5] << 8);
    case 5:
        b += key_p[4];
    case 4:
        a += ((unsigned long) key_p[3] << 24);
    case 3:
        a += ((unsigned long) key_p[2] << 16);
    case 2:
        a += ((unsigned long) key_p[1] << 8);
    case 1:
        a += key_p[0];
        /* case 0: nothing left to add */
    }
    HASH_MIX(a, b, c);

    return c;
}