static int set_request_vars(request_rec *r, enum auth_ldap_phase phase) { 
    char *prefix = NULL;
    int prefix_len;
    int remote_user_attribute_set = 0;
    authn_ldap_request_t *req =
        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);
    const char **vals = req->vals;

    prefix = (phase == LDAP_AUTHN) ? AUTHN_PREFIX : sec->authz_prefix;
    prefix_len = strlen(prefix);

    if (sec->attributes && vals) {
        apr_table_t *e = r->subprocess_env;
        int i = 0;
        while (sec->attributes[i]) {
            char *str = apr_pstrcat(r->pool, prefix, sec->attributes[i], NULL);
            int j = prefix_len;
            while (str[j]) {
                str[j] = apr_toupper(str[j]);
                j++;
            }
            apr_table_setn(e, str, vals[i] ? vals[i] : "");

            /* handle remote_user_attribute, if set */
            if ((phase == LDAP_AUTHN) &&
                sec->remote_user_attribute && 
                !strcmp(sec->remote_user_attribute, sec->attributes[i])) {
                r->user = (char *)apr_pstrdup(r->pool, vals[i]);
                remote_user_attribute_set = 1;
            }
            i++;
        }
    }
    return remote_user_attribute_set;
}