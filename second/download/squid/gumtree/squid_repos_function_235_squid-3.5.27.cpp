static void
InitLDAP(edui_ldap_t *l)
{
    if (l == NULL) return;

    l->lp = NULL;
    if (l->lm != NULL)
        ldap_msgfree(l->lm);
    if (l->val != NULL)
        ldap_value_free_len(l->val);
    l->lm = NULL;
    l->val = NULL;
    *(l->basedn) = '\0';
    *(l->host) = '\0';
    *(l->dn) = '\0';
    *(l->passwd) = '\0';
    *(l->search_filter) = '\0';
    *(l->userid) = '\0';
    memset(l->search_ip, '\0', sizeof(l->search_ip));
    l->status = 0;
    l->status |= LDAP_INIT_S;
    l->port = 0;
    l->scope = -1;
    l->type = 0;
    l->err = -1;                    /* Set error to LDAP_SUCCESS by default */
    l->ver = 0;
    l->idle_time = 0;
    l->num_ent = 0;                 /* Number of entries in l->lm */
    l->num_val = 0;                 /* Number of entries in l->val */

    /* Set default settings from conf */
    if (edui_conf.basedn[0] != '\0')
        xstrncpy(l->basedn, edui_conf.basedn, sizeof(l->basedn));
    if (edui_conf.host[0] != '\0')
        xstrncpy(l->host, edui_conf.host, sizeof(l->host));
    if (edui_conf.port != 0)
        l->port = edui_conf.port;
    if (edui_conf.dn[0] != '\0')
        xstrncpy(l->dn, edui_conf.dn, sizeof(l->dn));
    if (edui_conf.passwd[0] != '\0')
        xstrncpy(l->passwd, edui_conf.passwd, sizeof(l->passwd));
    if (edui_conf.search_filter[0] != '\0')
        xstrncpy(l->search_filter, edui_conf.search_filter, sizeof(l->search_filter));
    if (!(edui_conf.scope < 0))
        l->scope = edui_conf.scope;
}