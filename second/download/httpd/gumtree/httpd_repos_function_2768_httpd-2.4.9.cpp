static util_ldap_connection_t *get_connection_for_authz(request_rec *r, enum auth_ldap_optype type) {
    authn_ldap_request_t *req =
        (authn_ldap_request_t *)ap_get_module_config(r->request_config, &authnz_ldap_module);
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)ap_get_module_config(r->per_dir_config, &authnz_ldap_module);

    char *binddn = sec->binddn;
    char *bindpw = sec->bindpw;

    /* If the per-request config isn't set, we didn't authenticate this user, and leave the default credentials */
    if (req && req->password &&
         ((type == LDAP_SEARCH && sec->search_as_user)    ||
          (type == LDAP_COMPARE && sec->compare_as_user)  ||
          (type == LDAP_COMPARE_AND_SEARCH && sec->compare_as_user && sec->search_as_user))){
            binddn = req->dn;
            bindpw = req->password;
    }

    return util_ldap_connection_find(r, sec->host, sec->port,
                                     binddn, bindpw,
                                     sec->deref, sec->secure);
}