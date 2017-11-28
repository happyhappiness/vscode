static int
ip6_sa2str(sa6, buf, bufsiz, flags)
const struct sockaddr_in6 *sa6;
char *buf;
size_t bufsiz;
int flags;
{
    unsigned int ifindex;
    const struct in6_addr *a6;
    int n;

    ifindex = (unsigned int)sa6->sin6_scope_id;
    a6 = &sa6->sin6_addr;

#if NI_NUMERICSCOPE
    if ((flags & NI_NUMERICSCOPE) != 0) {
        n = snprintf(buf, bufsiz, "%u", sa6->sin6_scope_id);
        if (n < 0 || n >= bufsiz)
            return -1;
        else
            return n;
    }
#endif

    /* if_indextoname() does not take buffer size.  not a good api... */
    if ((IN6_IS_ADDR_LINKLOCAL(a6) || IN6_IS_ADDR_MC_LINKLOCAL(a6) ||
            IN6_IS_ADDR_MC_NODELOCAL(a6)) && bufsiz >= IF_NAMESIZE) {
        char *p = if_indextoname(ifindex, buf);
        if (p)
            return (strlen(p));
    }

    /* last resort */
    n = snprintf(buf, bufsiz, "%u", sa6->sin6_scope_id);
    if (n < 0 || n >= bufsiz)
        return -1;
    else
        return n;
}