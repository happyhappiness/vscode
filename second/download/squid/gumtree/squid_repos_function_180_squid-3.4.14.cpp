static int
SearchFilterLDAP(edui_ldap_t *l, char *group)
{
    size_t i, j, s;
    int swi;
    char bufa[EDUI_MAXLEN], bufb[EDUI_MAXLEN], bufc[EDUI_MAXLEN], bufd[EDUI_MAXLEN], bufg[EDUI_MAXLEN];
    if (l == NULL) return LDAP_ERR_NULL;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;			/* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;			/* Not open */
    if (!(l->status & LDAP_BIND_S)) return LDAP_ERR_BIND;			/* Not Bound */
    if (l->search_ip[0] == '\0') return LDAP_ERR_DATA;				/* Search IP is required */

    /* Zero out if not already */
    memset(bufa, '\0', sizeof(bufa));
    // using memset() for 'bufa' fixes the 64-bit issue
    *(bufb) = '\0';
    *(bufc) = '\0';
    *(bufd) = '\0';
    *(bufg) = '\0';

    s = strlen(l->search_ip);
    bufc[0] = '\134';
    swi = 0;
    j = 1;
    for (i = 0; i < s; ++i) {
        if (swi == 2) {
            bufc[j] = '\134';
            ++j;
            bufc[j] = l->search_ip[i];
            ++j;
            swi = 1;
        } else {
            bufc[j] = l->search_ip[i];
            ++j;
            ++swi;
        }
    }
    if (group == NULL) {
        /* No groupMembership= to add, yay! */
        xstrncpy(bufa, "(&", sizeof(bufa));
        strncat(bufa, edui_conf.search_filter, strlen(edui_conf.search_filter));
        /* networkAddress */
        snprintf(bufb, sizeof(bufb), "(|(networkAddress=1\\23%s)", bufc);
        if (l->status & LDAP_IPV4_S) {
            int ln = snprintf(bufd, sizeof(bufd), "(networkAddress=8\\23\\00\\00%s)(networkAddress=9\\23\\00\\00%s))", \
                              bufc, bufc);
            strncat(bufb, bufd, ln);
        } else if (l->status & LDAP_IPV6_S) {
            int ln = snprintf(bufd, sizeof(bufd), "(networkAddress=10\\23\\00\\00%s)(networkAddress=11\\23\\00\\00%s))", \
                              bufc, bufc);
            strncat(bufb, bufd, ln);
        } else
            strncat(bufb, ")", 1);
        strncat(bufa, bufb, strlen(bufb));
        strncat(bufa, ")", 1);
    } else {
        /* Needs groupMembership= to add... */
        xstrncpy(bufa, "(&(&", sizeof(bufa));
        strncat(bufa, edui_conf.search_filter, strlen(edui_conf.search_filter));
        /* groupMembership -- NOTE: Squid *MUST* provide "cn=" from squid.conf */
        snprintf(bufg, sizeof(bufg), "(groupMembership=%s", group);
        if ((l->basedn[0] != '\0') && (strstr(group, l->basedn) == NULL)) {
            strncat(bufg, ",", 1);
            strncat(bufg, l->basedn, strlen(l->basedn));
        }
        strncat(bufg, ")", 1);
        strncat(bufa, bufg, strlen(bufg));
        /* networkAddress */
        snprintf(bufb, sizeof(bufb), "(|(networkAddress=1\\23%s)", bufc);
        if (l->status & LDAP_IPV4_S) {
            int ln = snprintf(bufd, sizeof(bufd), "(networkAddress=8\\23\\00\\00%s)(networkAddress=9\\23\\00\\00%s))", \
                              bufc, bufc);
            strncat(bufb, bufd, ln);
        } else if (l->status & LDAP_IPV6_S) {
            int ln = snprintf(bufd, sizeof(bufd), "(networkAddress=10\\23\\00\\00%s)(networkAddress=11\\23\\00\\00%s))", \
                              bufc, bufc);
            strncat(bufb, bufd, ln);
        } else
            strncat(bufb, ")", 1);
        strncat(bufa, bufb, strlen(bufb));
        strncat(bufa, "))", 2);
    }
    s = strlen(bufa);
    xstrncpy(l->search_filter, bufa, sizeof(l->search_filter));
    return s;
}