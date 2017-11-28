int
create_ls(struct main_args *margs)
{
    char *np, *dp;
    char *p;
    struct lsstruct *lssp = NULL, *lsspn = NULL;
    /*
     *  netbios list format:
     *
     *     nlist=Pattern1[:Pattern2]
     *
     *     Pattern=ldap-server@Domain    ldap server Name for a specific Kerberos domain
     *                             lsstruct.domain=Domain, lsstruct.lserver=ldap server
     *
     *
     */
    p = margs->llist;
    np = margs->llist;
    debug((char *) "%s| %s: DEBUG: ldap server list %s\n", LogTime(), PROGRAM, margs->llist ? margs->llist : "NULL");
    dp = NULL;

    if (!p) {
        debug((char *) "%s| %s: DEBUG: No ldap servers defined.\n", LogTime(), PROGRAM);
        return (0);
    }
    while (*p) {        /* loop over group list */
        if (*p == '\n' || *p == '\r') {     /* Ignore CR and LF if exist */
            ++p;
            continue;
        }
        if (*p == '@') {    /* end of group name - start of domain name */
            if (p == np) {  /* empty group name not allowed */
                debug((char *) "%s| %s: DEBUG: No ldap servers defined for domain %s\n", LogTime(), PROGRAM, p);
                free_ls(lssp);
                return (1);
            }
            if (dp) {  /* end of domain name - twice */
                debug((char *) "%s| %s: @ is not allowed in server name %s@%s\n",LogTime(), PROGRAM,np,dp);
                free_ls(lssp);
                return(1);
            }
            *p = '\0';
            ++p;
            lssp = init_ls();
            lssp->lserver = xstrdup(np);
            lssp->next = lsspn;
            dp = p;     /* after @ starts new domain name */
        } else if (*p == ':') { /* end of group name or end of domain name */
            if (p == np) {  /* empty group name not allowed */
                debug((char *) "%s| %s: DEBUG: No ldap servers defined for domain %s\n", LogTime(), PROGRAM, p);
                free_ls(lssp);
                return (1);
            }
            *p = '\0';
            ++p;
            if (dp) {       /* end of domain name */
                lssp->domain = xstrdup(dp);
                dp = NULL;
            } else {        /* end of group name and no domain name */
                lssp = init_ls();
                lssp->lserver = xstrdup(np);
                lssp->next = lsspn;
            }
            lsspn = lssp;
            np = p;     /* after : starts new group name */
            debug((char *) "%s| %s: DEBUG: ldap server %s Domain %s\n", LogTime(), PROGRAM, lssp->lserver, lssp->domain?lssp->domain:"NULL");
        } else
            ++p;
    }
    if (p == np) {      /* empty group name not allowed */
        debug((char *) "%s| %s: DEBUG: No ldap servers defined for domain %s\n", LogTime(), PROGRAM, p);
        free_ls(lssp);
        return (1);
    }
    if (dp) {           /* end of domain name */
        lssp->domain = xstrdup(dp);
    } else {            /* end of group name and no domain name */
        lssp = init_ls();
        lssp->lserver = xstrdup(np);
        if (lsspn)      /* Have already an existing structure */
            lssp->next = lsspn;
    }
    debug((char *) "%s| %s: DEBUG: ldap server %s Domain %s\n", LogTime(), PROGRAM, lssp->lserver, lssp->domain?lssp->domain:"NULL");

    margs->lservs = lssp;
    return (0);
}