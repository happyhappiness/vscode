static void *create_authnz_ldap_dir_config(apr_pool_t *p, char *d)
{
    authn_ldap_config_t *sec =
        (authn_ldap_config_t *)apr_pcalloc(p, sizeof(authn_ldap_config_t));

    sec->pool = p;
#if APR_HAS_THREADS
    apr_thread_mutex_create(&sec->lock, APR_THREAD_MUTEX_DEFAULT, p);
#endif
/*
    sec->authz_enabled = 1;
*/
    sec->groupattr = apr_array_make(p, GROUPATTR_MAX_ELTS,
                                    sizeof(struct mod_auth_ldap_groupattr_entry_t));
    sec->subgroupclasses = apr_array_make(p, GROUPATTR_MAX_ELTS,
                                    sizeof(struct mod_auth_ldap_groupattr_entry_t));

    sec->have_ldap_url = 0;
    sec->url = "";
    sec->host = NULL;
    sec->binddn = NULL;
    sec->bindpw = NULL;
    sec->bind_authoritative = 1;
    sec->deref = always;
    sec->group_attrib_is_dn = 1;
    sec->secure = -1;   /*Initialize to unset*/
    sec->maxNestingDepth = 10;
    sec->sgAttributes = apr_pcalloc(p, sizeof (char *) * GROUPATTR_MAX_ELTS + 1);

    sec->user_is_dn = 0;
    sec->remote_user_attribute = NULL;
    sec->compare_dn_on_server = 0;

    sec->authz_prefix = AUTHZ_PREFIX;

    return sec;
}