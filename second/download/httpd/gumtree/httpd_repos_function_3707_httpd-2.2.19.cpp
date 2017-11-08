static char *conv_p2_quad(apr_uint64_t num, register int nbits,
                     char format, char *buf_end, register apr_size_t *len)
{
    register int mask = (1 << nbits) - 1;
    register char *p = buf_end;
    static const char low_digits[] = "0123456789abcdef";
    static const char upper_digits[] = "0123456789ABCDEF";
    register const char *digits = (format == 'X') ? upper_digits : low_digits;

    if (num <= APR_UINT32_MAX)
        return(conv_p2((apr_uint32_t)num, nbits, format, buf_end, len));

    do {
        *--p = digits[num & mask];
        num >>= nbits;
    }
    while (num);

    *len = buf_end - p;
    return (p);
}