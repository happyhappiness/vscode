const char *
xitoa(int num)
{
    static char buf[24];    /* 2^64 = 18446744073709551616 */
    snprintf(buf, sizeof(buf), "%d", num);
    return buf;
}