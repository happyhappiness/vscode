static authz_status fcgi_authz_check(request_rec *r,
                                     const char *require_line,
                                     const void *parsed_require_line)
{
    const char *fn = "fcgi_authz_check";
    const char *prov = apr_table_get(r->notes, AUTHZ_PROVIDER_NAME_NOTE);
    const fcgi_provider_conf *conf;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  APLOGNO(02527) "%s(%s)", fn, require_line);

    if (!prov) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      APLOGNO(02528) "%s: provider note isn't set", fn);
        return AUTHZ_GENERAL_ERROR;
    }

    conf = apr_hash_get(fcgi_authz_providers, prov, APR_HASH_KEY_STRING);
    if (!conf) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      APLOGNO(02529) "%s: can't find config for provider %s",
                      fn, prov);
        return AUTHZ_GENERAL_ERROR;
    }

    if (APLOGrdebug(r)) {
        log_provider_info(conf, r);
    }

    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    if (conf->is_authn) {
        /* combined authn/authz phase, so app won't be invoked for authz
         *
         * If the provider already successfully authorized this request, 
         * success.
         */
        fcgi_request_notes *rnotes = ap_get_module_config(r->request_config,
                                                        &authnz_fcgi_module);
        if (rnotes
            && rnotes->successful_authnz_provider
            && !strcmp(rnotes->successful_authnz_provider, conf->name)) {
            return AUTHZ_GRANTED;
        }
        else {
            return AUTHZ_DENIED;
        }
    }
    else {
        req_rsp(r, conf, NULL, AP_FCGI_APACHE_ROLE_AUTHORIZER_STR, NULL, NULL);

        if (r->status == HTTP_OK) {
            return AUTHZ_GRANTED;
        }
        else if (r->status == HTTP_INTERNAL_SERVER_ERROR) {
            return AUTHZ_GENERAL_ERROR;
        }
        else {
            return AUTHZ_DENIED;
        }
    }
}