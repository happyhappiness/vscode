int
xinet_pton(af, src, dst)
int af;
const char *src;
void *dst;
{
    switch (af) {
    case AF_INET:
        return (inet_pton4(src, dst));
    case AF_INET6:
        return (inet_pton6(src, dst));
    default:
        errno = EAFNOSUPPORT;
        return (-1);
    }
    /* NOTREACHED */
}