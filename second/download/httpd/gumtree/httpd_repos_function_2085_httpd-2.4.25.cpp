static apr_port_t parse_epsv_reply(const char *reply)
{
    const char *p;
    char *ep;
    long port;

    /* Reply syntax per RFC 2428: "229 blah blah (|||port|)" where '|'
     * can be any character in ASCII from 33-126, obscurely.  Verify
     * the syntax. */
    p = ap_strchr_c(reply, '(');
    if (p == NULL || !p[1] || p[1] != p[2] || p[1] != p[3]
        || p[4] == p[1]) {
        return 0;
    }

    errno = 0;
    port = strtol(p + 4, &ep, 10);
    if (errno || port < 1 || port > 65535 || ep[0] != p[1] || ep[1] != ')') {
        return 0;
    }

    return (apr_port_t)port;
}