static char *log_escape(char *q, const char *e, const char *p)
{
    for ( ; *p ; ++p) {
        ap_assert(q < e);
        if (test_char_table[*(unsigned char *)p]&T_ESCAPE_FORENSIC) {
            ap_assert(q+2 < e);
            *q++ = '%';
            ap_bin2hex(p, 1, q);
            q += 2;
        }
        else
            *q++ = *p;
    }
    ap_assert(q < e);
    *q = '\0';

    return q;
}