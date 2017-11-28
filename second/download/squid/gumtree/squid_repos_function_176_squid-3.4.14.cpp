static int
SetVerLDAP(edui_ldap_t *l, int v)
{
    int x;
    if (l == NULL) return LDAP_ERR_NULL;
    if ((v > 3) || (v < 1)) return LDAP_ERR_PARAM;
    if (l->lp == NULL) return LDAP_ERR_POINTER;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;		/* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;		/* Not open */
    if (l->status & LDAP_BIND_S) return LDAP_ERR_BIND;			/* Already bound */

    /* set version */
    x = ldap_set_option(l->lp, LDAP_OPT_PROTOCOL_VERSION, &v);
    if (x == LDAP_SUCCESS) {
        l->ver = v;
        l->err = x;							/* Set LDAP error code */
        return LDAP_ERR_SUCCESS;
    } else {
        l->err = x;							/* Set LDAP error code */
        return LDAP_ERR_FAILED;
    }
}