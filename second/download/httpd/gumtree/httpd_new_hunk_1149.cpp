    int rc;
    apr_ldap_url_desc_t *urld;
    apr_ldap_err_t *result;

    authn_ldap_config_t *sec = config;

    rc = apr_ldap_url_parse(cmd->pool, url, &(urld), &(result));
    if (rc != APR_SUCCESS) {
        return result->reason;
    }
    sec->url = apr_pstrdup(cmd->pool, url);

    /* Set all the values, or at least some sane defaults */
    if (sec->host) {
        char *p = apr_palloc(cmd->pool, strlen(sec->host) + strlen(urld->lud_host) + 2);
        strcpy(p, urld->lud_host);
        strcat(p, " ");
        strcat(p, sec->host);
