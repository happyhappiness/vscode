static int
_my_mbstowcs(int16_t * dst, uchar * src, int len)
{
    int i;
    int16_t val;

    for (i = 0; i < len; i++) {
        val = *src;
        SSVAL(dst, 0, val);
        dst++;
        src++;
        if (val == 0)
            break;
    }
    return i;
}