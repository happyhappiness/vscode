static int
ip6_parsenumeric(sa, addr, host, hostlen, flags)
const struct sockaddr *sa;
const char *addr;
char *host;
size_t hostlen;
int flags;
{
    int numaddrlen;
    char numaddr[512];

    if (inet_ntop(AF_INET6, addr, numaddr, sizeof(numaddr)) == NULL)
        return EAI_SYSTEM;

    numaddrlen = strlen(numaddr);
    if (numaddrlen + 1 > hostlen) /* don't forget terminator */
        return EAI_OVERFLOW;
    strncpy(host, numaddr, hostlen);

    if (((const struct sockaddr_in6 *)sa)->sin6_scope_id) {
        char zonebuf[SQUIDHOSTNAMELEN];
        int zonelen;

        zonelen = ip6_sa2str(
                      (const struct sockaddr_in6 *)(const void *)sa,
                      zonebuf, sizeof(zonebuf), flags);
        if (zonelen < 0)
            return EAI_OVERFLOW;
        if (zonelen + 1 + numaddrlen + 1 > hostlen)
            return EAI_OVERFLOW;

        /* construct <numeric-addr><delim><zoneid> */
        memcpy(host + numaddrlen + 1, zonebuf,
               (size_t)zonelen);
        host[numaddrlen] = SCOPE_DELIMITER;
        host[numaddrlen + 1 + zonelen] = '\0';
    }

    return 0;
}