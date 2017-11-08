static char *conv_apr_sockaddr(apr_sockaddr_t *sa, char *buf_end, apr_size_t *len)
{
    char *p = buf_end;
    int is_negative;
    apr_size_t sub_len;
    char *ipaddr_str;

    p = conv_10(sa->port, TRUE, &is_negative, p, &sub_len);
    *--p = ':';
    apr_sockaddr_ip_get(&ipaddr_str, sa);
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