static char *conv_in_addr(struct in_addr *ia, char *buf_end, apr_size_t *len)
{
    unsigned addr = ntohl(ia->s_addr);
    char *p = buf_end;
    int is_negative;
    apr_size_t sub_len;

    p = conv_10((addr & 0x000000FF)      , TRUE, &is_negative, p, &sub_len);
    *--p = '.';
    p = conv_10((addr & 0x0000FF00) >>  8, TRUE, &is_negative, p, &sub_len);
    *--p = '.';
    p = conv_10((addr & 0x00FF0000) >> 16, TRUE, &is_negative, p, &sub_len);
    *--p = '.';
    p = conv_10((addr & 0xFF000000) >> 24, TRUE, &is_negative, p, &sub_len);

    *len = buf_end - p;
    return (p);
}