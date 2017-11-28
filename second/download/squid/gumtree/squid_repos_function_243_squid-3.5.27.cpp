static int
SearchLDAP(edui_ldap_t *l, int scope, char *filter, char **attrs)
{
    int s;
    char ft[EDUI_MAXLEN];
    if (l == NULL) return LDAP_ERR_NULL;
    if ((scope < 0) || (filter == NULL)) return LDAP_ERR_PARAM;     /* If attrs is NULL, then all attrs will return */
    if (l->lp == NULL) return LDAP_ERR_POINTER;
    if (!(l->status & LDAP_INIT_S)) return LDAP_ERR_INIT;       /* Not initalized */
    if (!(l->status & LDAP_OPEN_S)) return LDAP_ERR_OPEN;       /* Not open */
    if (!(l->status & LDAP_BIND_S)) return LDAP_ERR_BIND;       /* Not bound */
    if (l->status & LDAP_SEARCH_S) return LDAP_ERR_SEARCHED;        /* Already searching */
    if (l->basedn[0] == '\0') return LDAP_ERR_DATA;         /* We require a basedn */
    if (l->lm != NULL)
        ldap_msgfree(l->lm);                        /* Make sure l->lm is empty */

    xstrncpy(ft, filter, sizeof(ft));

    /* We have a binded connection, with a free l->lm, so let's get this done */
    switch (scope) {
    case 0:
        s = ldap_search_s(l->lp, l->basedn, LDAP_SCOPE_BASE, ft, attrs, 0, &(l->lm));
        break;
    case 1:
        s = ldap_search_s(l->lp, l->basedn, LDAP_SCOPE_ONELEVEL, ft, attrs, 0, &(l->lm));
        break;
    case 2:
        s = ldap_search_s(l->lp, l->basedn, LDAP_SCOPE_SUBTREE, ft, attrs, 0, &(l->lm));
        break;
    default:
        /* Only search ONE by default */
        s = ldap_search_s(l->lp, l->basedn, LDAP_SCOPE_ONELEVEL, ft, attrs, 0, &(l->lm));
        break;
    }
    if (s == LDAP_SUCCESS) {
        l->status |= (LDAP_SEARCH_S);                   /* Mark as searched */
        l->err = s;
        l->idle_time = 0;                       /* Connection in use, reset idle timer */
        l->num_ent = ldap_count_entries(l->lp, l->lm);          /* Counted */
        return LDAP_ERR_SUCCESS;
    } else {
        l->err = s;
        l->num_ent = (-1);
        return LDAP_ERR_FAILED;
    }
}