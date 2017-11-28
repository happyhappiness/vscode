static int
OpenLDAP(edui_ldap_t *l, char *h, unsigned int p)
{
    if ((l == NULL) || (h == NULL)) return LDAP_ERR_NULL;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;       /* Not initalized, or might be in use */
    if (l->status & LDAP_OPEN_S) return LDAP_ERR_OPEN;          /* Already open */
    if (l->status & LDAP_BIND_S) return LDAP_ERR_BIND;          /* Already bound */

    xstrncpy(l->host, h, sizeof(l->host));
    if (p > 0)
        l->port = p;
    else
        l->port = LDAP_PORT;                        /* Default is port 389 */

#ifdef NETSCAPE_SSL
    if (l->port == LDAPS_PORT)
        l->status |= (LDAP_SSL_S | LDAP_TLS_S);             /* SSL Port: 636 */
#endif

#ifdef USE_LDAP_INIT
    l->lp = ldap_init(l->host, l->port);
#else
    l->lp = ldap_open(l->host, l->port);
#endif
    if (l->lp == NULL) {
        l->err = LDAP_CONNECT_ERROR;
        return LDAP_ERR_CONNECT;                    /* Unable to connect */
    } else {
        /* set status */
//    l->status &= ~(LDAP_INIT_S);
        l->status |= LDAP_OPEN_S;
        l->err = LDAP_SUCCESS;
        return LDAP_ERR_SUCCESS;
    }
}