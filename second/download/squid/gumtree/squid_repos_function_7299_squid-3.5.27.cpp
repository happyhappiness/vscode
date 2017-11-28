const char *
xint64toa(int64_t num)
{
    static char buf[24];    /* 2^64 = 18446744073709551616 */
    snprintf(buf, sizeof(buf), "%" PRId64, num);
    return buf;
}