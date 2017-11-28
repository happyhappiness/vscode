static int
ResetLDAP(edui_ldap_t *l)
{
    if (l == NULL) return LDAP_ERR_NULL;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;                 /* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;                 /* Not open */
    if (!(l->status & LDAP_BIND_S)) return LDAP_ERR_BIND;                 /* Not bound */
    if (!(l->status & LDAP_PERSIST_S)) return LDAP_ERR_PERSIST;           /* Not persistent */

    /* Cleanup data struct */
    if (l->status & LDAP_VAL_S)
        l->status &= ~(LDAP_VAL_S);
    if (l->status & LDAP_SEARCH_S)
        l->status &= ~(LDAP_SEARCH_S);
    if (l->status & LDAP_IPV4_S)
        l->status &= ~(LDAP_IPV4_S);
    if (l->status & LDAP_IPV6_S)
        l->status &= ~(LDAP_IPV6_S);
    if (l->lm != NULL) {
        ldap_msgfree(l->lm);
        l->lm = NULL;
    }
    if (l->val != NULL) {
        ldap_value_free_len(l->val);
        l->val = NULL;
    }
    memset(l->search_ip, '\0', sizeof(l->search_ip));
    *(l->search_filter) = '\0';
    xstrncpy(l->search_filter, edui_conf.search_filter, sizeof(l->search_filter));
    *(l->userid) = '\0';
    if (!(l->status & LDAP_IDLE_S))
        l->status |= LDAP_IDLE_S;                                           /* Set idle mode */
    l->num_ent = 0;
    l->num_val = 0;
    l->err = LDAP_SUCCESS;
    return LDAP_ERR_SUCCESS;
}