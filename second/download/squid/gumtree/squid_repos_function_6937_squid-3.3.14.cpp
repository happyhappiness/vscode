int
xgetnameinfo(sa, salen, host, hostlen, serv, servlen, flags)
const struct sockaddr *sa;
socklen_t salen;
char *host;
size_t hostlen;
char *serv;
size_t servlen;
int flags;
{
    const struct afd *afd;
    struct servent *sp;
    struct hostent *hp;
    unsigned short port;
    int family, i;
    const char *addr;
    uint32_t v4a;
    char numserv[512];

    if (sa == NULL)
        return EAI_FAIL;

#if HAVE_SA_LEN	/*XXX*/
    if (sa->sa_len != salen)
        return EAI_FAIL;
#endif

    family = sa->sa_family;
    for (i = 0; afdl[i].a_af; i++)
        if (afdl[i].a_af == family) {
            afd = &afdl[i];
            goto found;
        }
    return EAI_FAMILY;

found:
    if (salen != afd->a_socklen)
        return EAI_FAIL;

    /* network byte order */
    memcpy(&port, (const char *)sa + afd->a_portoff, sizeof(port));
    addr = (const char *)sa + afd->a_off;

    if (serv == NULL || servlen == 0) {
        /*
         * do nothing in this case.
         * in case you are wondering if "&&" is more correct than
         * "||" here: RFC3493 says that serv == NULL OR servlen == 0
         * means that the caller does not want the result.
         */
    } else {
        if (flags & NI_NUMERICSERV)
            sp = NULL;
        else {
            sp = getservbyport(port,
                               (flags & NI_DGRAM) ? "udp" : "tcp");
        }
        if (sp) {
            if (strlen(sp->s_name) + 1 > servlen)
                return EAI_OVERFLOW;
            strncpy(serv, sp->s_name, servlen);
        } else {
            snprintf(numserv, sizeof(numserv), "%u", ntohs(port));
            if (strlen(numserv) + 1 > servlen)
                return EAI_OVERFLOW;
            strncpy(serv, numserv, servlen);
        }
    }

    switch (sa->sa_family) {
    case AF_INET:
        v4a = (uint32_t)
              ntohl(((const struct sockaddr_in *)sa)->sin_addr.s_addr);
        if (IN_MULTICAST(v4a) || IN_EXPERIMENTAL(v4a))
            flags |= NI_NUMERICHOST;
        v4a >>= IN_CLASSA_NSHIFT;
        if (v4a == 0)
            flags |= NI_NUMERICHOST;
        break;
#if INET6
    case AF_INET6: {
        const struct sockaddr_in6 *sin6;
        sin6 = (const struct sockaddr_in6 *)sa;
        switch (sin6->sin6_addr.s6_addr[0]) {
        case 0x00:
            if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr))
                ;
            else if (IN6_IS_ADDR_LOOPBACK(&sin6->sin6_addr))
                ;
            else
                flags |= NI_NUMERICHOST;
            break;
        default:
            if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))
                flags |= NI_NUMERICHOST;
            else if (IN6_IS_ADDR_MULTICAST(&sin6->sin6_addr))
                flags |= NI_NUMERICHOST;
            break;
        }
    }
    break;
#endif
    }
    if (host == NULL || hostlen == 0) {
        /*
         * do nothing in this case.
         * in case you are wondering if "&&" is more correct than
         * "||" here: RFC3493 says that host == NULL or hostlen == 0
         * means that the caller does not want the result.
         */
    } else if (flags & NI_NUMERICHOST) {
        /* NUMERICHOST and NAMEREQD conflicts with each other */
        if (flags & NI_NAMEREQD)
            return EAI_NONAME;

        goto numeric;
    } else {
#if USE_GETIPNODEBY
        int h_error = 0;
        hp = getipnodebyaddr(addr, afd->a_addrlen, afd->a_af, &h_error);
#else
        hp = gethostbyaddr(addr, afd->a_addrlen, afd->a_af);
#if 0 // getnameinfo.c:161:9: error: variable 'h_error' set but not used
#if HAVE_H_ERRNO
        h_error = h_errno;
#else
        h_error = EINVAL;
#endif
#endif /* 0 */
#endif

        if (hp) {
#if 0
            if (flags & NI_NOFQDN) {
                /*
                 * According to RFC3493 section 6.2, NI_NOFQDN
                 * means "node name portion of the FQDN shall
                 * be returned for local hosts."  The following
                 * code tries to implement it by returning the
                 * first label (the part before the first
                 * period) of the FQDN.  However, it is not
                 * clear if this always makes sense, since the
                 * given address may be outside of "local
                 * hosts."  Due to the unclear description, we
                 * disable the code in this implementation.
                 */
                char *p;
                p = strchr(hp->h_name, '.');
                if (p)
                    *p = '\0';
            }
#endif
            if (strlen(hp->h_name) + 1 > hostlen) {
#if USE_GETIPNODEBY
                freehostent(hp);
#endif
                return EAI_OVERFLOW;
            }
            strncpy(host, hp->h_name, hostlen);
#if USE_GETIPNODEBY
            freehostent(hp);
#endif
        } else {
            if (flags & NI_NAMEREQD)
                return EAI_NONAME;

numeric:
            switch (afd->a_af) {
#if INET6
            case AF_INET6: {
                int error;

                if ((error = ip6_parsenumeric(sa, addr, host,
                                              hostlen,
                                              flags)) != 0)
                    return(error);
                break;
            }
#endif
            default:
                if (inet_ntop(afd->a_af, addr, host,
                              hostlen) == NULL)
                    return EAI_SYSTEM;
                break;
            }
        }
    }
    return(0);
}