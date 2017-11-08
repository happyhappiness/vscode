static char *conv_apr_sockaddr(apr_sockaddr_t *sa, char *buf_end, apr_size_t *len)
{
    char *p = buf_end;
    int is_negative;
    apr_size_t sub_len;
    char *ipaddr_str;

    p = conv_10(sa->port, TRUE, &is_negative, p, &sub_len);
    *--p = ':';
    ipaddr_str = buf_end - NUM_BUF_SIZE;
    if (apr_sockaddr_ip_getbuf(ipaddr_str, sa->addr_str_len, sa)) {
        /* Should only fail if the buffer is too small, which it
         * should not be; but fail safe anyway: */
        *--p = '?';
        *len = buf_end - p;
        return p;
    }
    sub_len = strlen(ipaddr_str);
#if APR_HAVE_IPV6
    if (sa->family == APR_INET6 &&
        !IN6_IS_ADDR_V4MAPPED(&sa->sa.sin6.sin6_addr)) {
        *(p - 1) = ']';
        p -= sub_len + 2;
        *p = '[';
        memcpy(p + 1, ipaddr_str, sub_len);
    }
    else
#endif
    {
        p -= sub_len;
        memcpy(p, ipaddr_str, sub_len);
    }

    *len = buf_end - p;
    return (p);
}