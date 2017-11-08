static int ftp_check_string(const char *x)
{
    int i, ch = 0;
#if APR_CHARSET_EBCDIC
    char buf[1];
#endif

    for (i = 0; x[i] != '\0'; i++) {
        ch = x[i];
        if (ch == '%' && apr_isxdigit(x[i + 1]) && apr_isxdigit(x[i + 2])) {
            ch = ap_proxy_hex2c(&x[i + 1]);
            i += 2;
        }
#if !APR_CHARSET_EBCDIC
        if (ch == '\015' || ch == '\012' || (ch & 0x80))
#else                           /* APR_CHARSET_EBCDIC */
        if (ch == '\r' || ch == '\n')
            return 0;
        buf[0] = ch;
        ap_xlate_proto_to_ascii(buf, 1);
        if (buf[0] & 0x80)
#endif                          /* APR_CHARSET_EBCDIC */
            return 0;
    }
    return 1;
}