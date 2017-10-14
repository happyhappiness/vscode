int mod_auth_ldap_check_user_id(request_rec *r)
{
    int failures = 0;
    const char **vals = NULL;
    char filtbuf[FILTER_LENGTH];
    mod_auth_ldap_config_t *sec =
        (mod_auth_ldap_config_t *)ap_get_module_config(r->per_dir_config, &auth_ldap_module);

    util_ldap_connection_t *ldc = NULL;
    const char *sent_pw;
    int result = 0;
    const char *dn = NULL;

    mod_auth_ldap_request_t *req =
        (mod_auth_ldap_request_t *)apr_pcalloc(r->pool, sizeof(mod_auth_ldap_request_t));
    ap_set_module_config(r->request_config, &auth_ldap_module, req);

    if (!sec->enabled) {
        return DECLINED;
    }

    /* 
     * Basic sanity checks before any LDAP operations even happen.
     */
    if (!sec->have_ldap_url) {
        return DECLINED;
    }

start_over:

    /* There is a good AuthLDAPURL, right? */
    if (sec->host) {
        ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                       sec->binddn, sec->bindpw, sec->deref,
                                       sec->secure);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r, 
                      "[%d] auth_ldap authenticate: no sec->host - weird...?", getpid());
        return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
		  "[%d] auth_ldap authenticate: using URL %s", getpid(), sec->url);

    /* Get the password that the client sent */
    if ((result = ap_get_basic_auth_pw(r, &sent_pw))) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
		      "[%d] auth_ldap authenticate: "
		      "ap_get_basic_auth_pw() returns %d", getpid(), result);
        util_ldap_connection_close(ldc);
        return result;
    }

    if (r->user == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
		      "[%d] auth_ldap authenticate: no user specified", getpid());
        util_ldap_connection_close(ldc);
        return sec->auth_authoritative? HTTP_UNAUTHORIZED : DECLINED;
    }

    /* build the username filter */
    mod_auth_ldap_build_filter(filtbuf, r, sec);

    /* do the user search */
    result = util_ldap_cache_checkuserid(r, ldc, sec->url, sec->basedn, sec->scope,
                                         sec->attributes, filtbuf, sent_pw, &dn, &vals);
    util_ldap_connection_close(ldc);

    /* sanity check - if server is down, retry it up to 5 times */
    if (result == LDAP_SERVER_DOWN) {
        if (failures++ <= 5) {
            goto start_over;
        }
    }

    /* handle bind failure */
    if (result != LDAP_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r, 
                      "[%d] auth_ldap authenticate: "
                      "user %s authentication failed; URI %s [%s][%s]",
		      getpid(), r->user, r->uri, ldc->reason, ldap_err2string(result));
        if ((LDAP_INVALID_CREDENTIALS == result) || sec->auth_authoritative) {
            ap_note_basic_auth_failure(r);
            return HTTP_UNAUTHORIZED;
        }
        else {
            return DECLINED;
        }
    }

    /* mark the user and DN */
    req->dn = apr_pstrdup(r->pool, dn);
    req->user = r->user;
    if (sec->user_is_dn) {
        r->user = req->dn;
    }

    /* add environment variables */
    if (sec->attributes && vals) {
        apr_table_t *e = r->subprocess_env;
        int i = 0;
        while (sec->attributes[i]) {
            char *str = apr_pstrcat(r->pool, "AUTHENTICATE_", sec->attributes[i], NULL);
            int j = 13;
            while (str[j]) {
                if (str[j] >= 'a' && str[j] <= 'z') {
                    str[j] = str[j] - ('a' - 'A');
                }
                j++;
            }
            apr_table_setn(e, str, vals[i]);
            i++;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
		  "[%d] auth_ldap authenticate: accepting %s", getpid(), r->user);

    return OK;
}