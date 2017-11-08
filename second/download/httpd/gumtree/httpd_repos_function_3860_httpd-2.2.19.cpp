apr_status_t apr_socket_create(apr_socket_t **new, int ofamily, int type,
                               int protocol, apr_pool_t *cont)
{
    int family = ofamily, flags = 0;

#ifdef HAVE_SOCK_CLOEXEC
    flags |= SOCK_CLOEXEC;
#endif

    if (family == APR_UNSPEC) {
#if APR_HAVE_IPV6
        family = APR_INET6;
#else
        family = APR_INET;
#endif
    }

    alloc_socket(new, cont);

#ifndef BEOS_R5
    (*new)->socketdes = socket(family, type|flags, protocol);
#else
    /* For some reason BeOS R5 has an unconventional protocol numbering,
     * so we need to translate here. */
    switch (protocol) {
    case 0:
        (*new)->socketdes = socket(family, type|flags, 0);
        break;
    case APR_PROTO_TCP:
        (*new)->socketdes = socket(family, type|flags, IPPROTO_TCP);
        break;
    case APR_PROTO_UDP:
        (*new)->socketdes = socket(family, type|flags, IPPROTO_UDP);
        break;
    case APR_PROTO_SCTP:
    default:
        errno = EPROTONOSUPPORT;
        (*new)->socketdes = -1;
        break;
    }
#endif /* BEOS_R5 */

#if APR_HAVE_IPV6
    if ((*new)->socketdes < 0 && ofamily == APR_UNSPEC) {
        family = APR_INET;
        (*new)->socketdes = socket(family, type|flags, protocol);
    }
#endif

    if ((*new)->socketdes < 0) {
        return errno;
    }
    set_socket_vars(*new, family, type, protocol);

#ifndef HAVE_SOCK_CLOEXEC
    {
        int flags;

        if ((flags = fcntl((*new)->socketdes, F_GETFD)) == -1)
            return errno;

        flags |= FD_CLOEXEC;
        if (fcntl((*new)->socketdes, F_SETFD, flags) == -1)
            return errno;
    }
#endif

    (*new)->timeout = -1;
    (*new)->inherit = 0;
    apr_pool_cleanup_register((*new)->pool, (void *)(*new), socket_cleanup,
                              socket_cleanup);

    return APR_SUCCESS;
}