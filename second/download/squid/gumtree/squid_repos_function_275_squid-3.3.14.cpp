int
create_gd(struct main_args *margs)
{
    char *gp, *dp;
    char *p;
    struct gdstruct *gdsp = NULL, *gdspn = NULL;
    /*
     *  Group list format:
     *
     *     glist=Pattern1[:Pattern2]
     *
     *     Pattern=Group           Group for all domains(including non Kerberos domains using ldap url options) if no
     *                             other group definition for domain exists or users without
     *                             domain information.
     *                             gdstruct.domain=NULL, gdstruct.group=Group
     *
     *  or Pattern=Group@          Group for all Kerberos domains if no other group definition
     *                             exists
     *                             gdstruct.domain="", gdstruct.group=Group
     *
     *  or Pattern=Group@Domain    Group for a specific Kerberos domain
     *                             gdstruct.domain=Domain, gdstruct.group=Group
     *
     *
     */
    char *hp1 = hex_utf_char(margs, 0);
    char *hp2 = hex_utf_char(margs, 1);
    char *up = utf8dup(margs);

    // NP: will point to the start of a temporary assembly buffer used by 'p' and 'gp'
    //     for catenation of the hp1, hp2, and up buffer contents from above.
    //     necessary for xfree() because both p and gp move over the assembly area
    char *gpbuf = NULL;

    // release the allocated UTF decoding buffers
#define cleanup() { \
    xfree(gpbuf); \
    xfree(hp1); \
    xfree(hp2); \
    xfree(up); \
    free_gd(gdsp); \
 }

    p = up;
    if (hp1) {
        if (hp2) {
            if (up) {
                gpbuf = p = (char *) xmalloc(strlen(up) + strlen(hp1) + strlen(hp2) + 2);
                strcpy(p, up);
                strcat(p, ":");
                strcat(p, hp1);
                strcat(p, ":");
                strcat(p, hp2);
            } else {
                gpbuf = p = (char *) xmalloc(strlen(hp1) + strlen(hp2) + 1);
                strcpy(p, hp1);
                strcat(p, ":");
                strcat(p, hp2);
            }
        } else {
            if (up) {
                gpbuf = p = (char *) xmalloc(strlen(up) + strlen(hp1) + 1);
                strcpy(p, up);
                strcat(p, ":");
                strcat(p, hp1);
            } else
                p = hp1;
        }
    } else {
        if (hp2) {
            if (up) {
                gpbuf = p = (char *) xmalloc(strlen(up) + strlen(hp2) + 1);
                strcpy(p, up);
                strcat(p, ":");
                strcat(p, hp2);
            } else
                p = hp2;
        } else
            p = up;
    }
    gp = p;
    debug((char *) "%s| %s: INFO: Group list %s\n", LogTime(), PROGRAM, p ? p : "NULL");
    dp = NULL;

    if (!p) {
        debug((char *) "%s| %s: ERROR: No groups defined.\n", LogTime(), PROGRAM);
        cleanup();
        return (1);
    }
    while (*p) {		/* loop over group list */
        if (*p == '\n' || *p == '\r') {		/* Ignore CR and LF if exist */
            ++p;
            continue;
        }
        if (*p == '@') {	/* end of group name - start of domain name */
            if (p == gp) {	/* empty group name not allowed */
                debug((char *) "%s| %s: ERROR: No group defined for domain %s\n", LogTime(), PROGRAM, p);
                cleanup();
                return (1);
            }
            if (dp) {  /* end of domain name - twice */
                debug((char *) "%s| %s: @ is not allowed in group name %s@%s\n",LogTime(), PROGRAM,gp,dp);
                cleanup();
                return(1);
            }
            *p = '\0';
            ++p;
            gdsp = init_gd();
            gdsp->group = xstrdup(gp);
            gdsp->next = gdspn;
            dp = p;		/* after @ starts new domain name */
        } else if (*p == ':') {	/* end of group name or end of domain name */
            if (p == gp) {	/* empty group name not allowed */
                debug((char *) "%s| %s: ERROR: No group defined for domain %s\n", LogTime(), PROGRAM, p);
                cleanup();
                return (1);
            }
            *p = '\0';
            ++p;
            if (dp) {		/* end of domain name */
                gdsp->domain = xstrdup(dp);
                dp = NULL;
            } else {		/* end of group name and no domain name */
                gdsp = init_gd();
                gdsp->group = xstrdup(gp);
                gdsp->next = gdspn;
            }
            gdspn = gdsp;
            gp = p;		/* after : starts new group name */
            debug((char *) "%s| %s: INFO: Group %s  Domain %s\n", LogTime(), PROGRAM, gdsp->group, gdsp->domain ? gdsp->domain : "NULL");
        } else
            ++p;
    }
    if (p == gp) {		/* empty group name not allowed */
        debug((char *) "%s| %s: ERROR: No group defined for domain %s\n", LogTime(), PROGRAM, p);
        cleanup();
        return (1);
    }
    if (dp) {			/* end of domain name */
        gdsp->domain = xstrdup(dp);
    } else {			/* end of group name and no domain name */
        gdsp = init_gd();
        gdsp->group = xstrdup(gp);
        if (gdspn)		/* Have already an existing structure */
            gdsp->next = gdspn;
    }
    debug((char *) "%s| %s: INFO: Group %s  Domain %s\n", LogTime(), PROGRAM, gdsp->group, gdsp->domain ? gdsp->domain : "NULL");

    margs->groups = gdsp;
    gdsp = NULL; // prevent the cleanup() deallocating it.
    cleanup();
    return (0);
}