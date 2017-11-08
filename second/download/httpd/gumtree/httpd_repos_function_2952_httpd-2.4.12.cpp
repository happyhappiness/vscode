static authn_status fcgi_check_password(request_rec *r, const char *user,
                                        const char *password)
{
    const char *fn = "fcgi_check_password";
    const char *prov = apr_table_get(r->notes, AUTHN_PROVIDER_NAME_NOTE);
    const fcgi_provider_conf *conf;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  APLOGNO(02524) "%s(%s, XXX): provider %s",
                  fn, user, prov);

    if (!prov) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      APLOGNO(02525) "%s: provider note isn't set", fn);
        return AUTH_GENERAL_ERROR;
    }

    conf = apr_hash_get(fcgi_authn_providers, prov, APR_HASH_KEY_STRING);
    if (!conf) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      APLOGNO(02526) "%s: can't find config for provider %s",
                      fn, prov);
        return AUTH_GENERAL_ERROR;
    }

    if (APLOGrdebug(r)) {
        log_provider_info(conf, r);
    }

    req_rsp(r, conf, password, 
            /* combined authn and authz: FCGI_APACHE_ROLE not set */
            conf->is_authz ? NULL : AP_FCGI_APACHE_ROLE_AUTHENTICATOR_STR,
            NULL, NULL);

    if (r->status == HTTP_OK) {
        if (conf->is_authz) {
            /* combined authn/authz phase, so app won't be invoked for authz
             *
             * Remember that the request was successfully authorized by this
             * provider.
             */
            fcgi_request_notes *rnotes = apr_palloc(r->pool, sizeof(*rnotes));
            rnotes->successful_authnz_provider = conf->name;
            ap_set_module_config(r->request_config, &authnz_fcgi_module,
                                 rnotes);
        }
        return AUTH_GRANTED;
    }
    else if (r->status == HTTP_INTERNAL_SERVER_ERROR) {
        return AUTH_GENERAL_ERROR;
    }
    else {
        return AUTH_DENIED;
    }
}