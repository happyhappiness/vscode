void
CvtBin(const HASHHEX Hex, HASH Bin)
{
    unsigned short i;
    unsigned char j;

    for (i = 0; i < HASHHEXLEN; i++) {
        unsigned char n;
        j = Hex[i];
        if (('0' <= j) && (j <= '9'))
            n = j - '0';
        else if (('a' <= j) && (j <= 'f'))
            n = j - 'a' + 10;
        else if (('A' <= j) && (j <= 'F'))
            n = j - 'A' + 10;
        else
            continue;
        if (i % 2 == 0)
            Bin[i / 2] = n << 4;
        else
            Bin[i / 2] |= n;
    }

#if HASHHEXLEN != (2*HASHLEN)
    /*
      Why? :: right here i == 32
        which means the first step of the for loop makes i==16
        and cannot be < HASHLEN (which is also 16)

      But only guaranteed if HASHHEXLEN == 2*HASHLEN
      This will ensure correct 0-ing of bins no matter what.
    */
    for (i = i / 2; i < HASHLEN; i++) {
        Bin[i] = '\0';
    }
#endif
}