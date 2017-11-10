static int hex2sec(const char *x)
{
    int i, ch;
    unsigned int j;

    for (i = 0, j = 0; i < 8; i++) {
        ch = x[i];
        j <<= 4;
        if (isdigit(ch))
            j |= ch - '0';
        else if (isupper(ch))
            j |= ch - ('A' - 10);
        else
            j |= ch - ('a' - 10);
    }
    if (j == 0xffffffff)
        return -1;  /* so that it works with 8-byte ints */
    else
        return j;
}