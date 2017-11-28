static int
CloseLDAP(edui_ldap_t *l)
{
    int s;
    if (l == NULL) return LDAP_ERR_NULL;
    if (l->lp == NULL) return LDAP_ERR_NULL;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;       /* Connection not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;       /* Connection not open */

    if (l->lm != NULL) {
        ldap_msgfree(l->lm);
        l->lm = NULL;
    }
    if (l->val != NULL) {
        ldap_value_free_len(l->val);
        l->val = NULL;
    }

    /* okay, so it's open, close it - No need to check other criteria */
    s = ldap_unbind(l->lp);
    if (s == LDAP_SUCCESS) {
        l->status = LDAP_INIT_S;
        l->idle_time = 0;
        l->err = s;                         /* Set LDAP error code */
        return LDAP_ERR_SUCCESS;
    } else {
        l->err = s;                         /* Set LDAP error code */
        return LDAP_ERR_FAILED;
    }
}