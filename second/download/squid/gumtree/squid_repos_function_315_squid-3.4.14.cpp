int
create_nd(struct main_args *margs)
{
    char *np, *dp;
    char *p;
    struct ndstruct *ndsp = NULL, *ndspn = NULL;
    /*
     *  netbios list format:
     *
     *     nlist=Pattern1[:Pattern2]
     *
     *     Pattern=NetbiosName@Domain    Netbios Name for a specific Kerberos domain
     *                             ndstruct.domain=Domain, ndstruct.netbios=NetbiosName
     *
     *
     */
    p = margs->nlist;
    np = margs->nlist;
    debug((char *) "%s| %s: DEBUG: Netbios list %s\n", LogTime(), PROGRAM, margs->nlist ? margs->nlist : "NULL");
    dp = NULL;

    if (!p) {
        debug((char *) "%s| %s: DEBUG: No netbios names defined.\n", LogTime(), PROGRAM);
        return (0);
    }
    while (*p) {		/* loop over group list */
        if (*p == '\n' || *p == '\r') {		/* Ignore CR and LF if exist */
            ++p;
            continue;
        }
        if (*p == '@') {	/* end of group name - start of domain name */
            if (p == np) {	/* empty group name not allowed */
                debug((char *) "%s| %s: DEBUG: No netbios name defined for domain %s\n", LogTime(), PROGRAM, p);
                free_nd(ndsp);
                return (1);
            }
            if (dp) {  /* end of domain name - twice */
                debug((char *) "%s| %s: @ is not allowed in netbios name %s@%s\n",LogTime(), PROGRAM,np,dp);
                free_nd(ndsp);
                return(1);
            }
            *p = '\0';
            ++p;
            ndsp = init_nd();
            ndsp->netbios = xstrdup(np);
            ndsp->next = ndspn;
            dp = p;		/* after @ starts new domain name */
        } else if (*p == ':') {	/* end of group name or end of domain name */
            if (p == np) {	/* empty group name not allowed */
                debug((char *) "%s| %s: DEBUG: No netbios name defined for domain %s\n", LogTime(), PROGRAM, p);
                free_nd(ndsp);
                return (1);
            }
            *p = '\0';
            ++p;
            if (dp) {		/* end of domain name */
                ndsp->domain = xstrdup(dp);
                dp = NULL;
            } else {		/* end of group name and no domain name */
                ndsp = init_nd();
                ndsp->netbios = xstrdup(np);
                ndsp->next = ndspn;
            }
            ndspn = ndsp;
            np = p;		/* after : starts new group name */
            if (!ndsp->domain || !strcmp(ndsp->domain, "")) {
                debug((char *) "%s| %s: DEBUG: No domain defined for netbios name %s\n", LogTime(), PROGRAM, ndsp->netbios);
                free_nd(ndsp);
                return (1);
            }
            debug((char *) "%s| %s: DEBUG: Netbios name %s  Domain %s\n", LogTime(), PROGRAM, ndsp->netbios, ndsp->domain);
        } else
            ++p;
    }
    if (p == np) {		/* empty group name not allowed */
        debug((char *) "%s| %s: DEBUG: No netbios name defined for domain %s\n", LogTime(), PROGRAM, p);
        free_nd(ndsp);
        return (1);
    }
    if (dp) {			/* end of domain name */
        ndsp->domain = xstrdup(dp);
    } else {			/* end of group name and no domain name */
        ndsp = init_nd();
        ndsp->netbios = xstrdup(np);
        ndsp->next = ndspn;
    }
    if (!ndsp->domain || !strcmp(ndsp->domain, "")) {
        debug((char *) "%s| %s: DEBUG: No domain defined for netbios name %s\n", LogTime(), PROGRAM, ndsp->netbios);
        free_nd(ndsp);
        return (1);
    }
    debug((char *) "%s| %s: DEBUG: Netbios name %s  Domain %s\n", LogTime(), PROGRAM, ndsp->netbios, ndsp->domain);

    margs->ndoms = ndsp;
    return (0);
}