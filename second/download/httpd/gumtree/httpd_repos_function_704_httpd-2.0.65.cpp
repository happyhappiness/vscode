void ssl_util_uuencode_binary(unsigned char *szTo,
                              const unsigned char *szFrom,
                              int nLength, BOOL bPad)
{
    const unsigned char *s;
    int nPad = 0;

    for (s = szFrom; nLength > 0; s += 3) {
        *szTo++ = ssl_util_uuencode_six2pr[s[0] >> 2];
        *szTo++ = ssl_util_uuencode_six2pr[(s[0] << 4 | s[1] >> 4) & 0x3f];
        if (--nLength == 0) {
            nPad = 2;
            break;
        }
        *szTo++ = ssl_util_uuencode_six2pr[(s[1] << 2 | s[2] >> 6) & 0x3f];
        if (--nLength == 0) {
            nPad = 1;
            break;
        }
        *szTo++ = ssl_util_uuencode_six2pr[s[2] & 0x3f];
        --nLength;
    }
    while(bPad && nPad--) {
        *szTo++ = NUL;
    }
    *szTo = NUL;
    return;
}