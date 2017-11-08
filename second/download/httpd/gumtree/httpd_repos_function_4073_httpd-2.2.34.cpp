static APR_INLINE unsigned char *c2x(unsigned what, unsigned char prefix,
        unsigned char *where)
{
#if APR_CHARSET_EBCDIC
    what = convert_e2a[(unsigned char)what];
#endif /*APR_CHARSET_EBCDIC*/
    *where++ = prefix;
    *where++ = c2x_table[what >> 4];
    *where++ = c2x_table[what & 0xf];
    return where;
}