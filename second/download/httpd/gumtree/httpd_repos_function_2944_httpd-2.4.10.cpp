static int fcgi_check_authn(request_rec *r)
{
    const char *fn = "fcgi_check_authn";
    fcgi_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                &authnz_fcgi_module);
    const char *password = NULL;
    const fcgi_provider_conf *conf;
    const char *prov;
    const char *auth_type;
    char rspbuf[NON200_RESPONSE_BUF_LEN + 1]; /* extra byte for '\0' */
    apr_size_t rspbuflen = sizeof rspbuf - 1;
    int res;

    prov = dconf && dconf->name ? dconf->name : NULL;

    if (!prov || !strcasecmp(prov, "None")) {
        return DECLINED;
    }

    auth_type = ap_auth_type(r);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  APLOGNO(02516) "%s, prov %s, authoritative %s, "
                  "require-basic %s, user expr? %s type %s",
                  fn, prov,
                  dconf->authoritative ? "yes" : "no",
                  dconf->require_basic_auth ? "yes" : "no",
                  dconf->user_expr ? "yes" : "no",
                  auth_type);

    if (auth_type && !strcasecmp(auth_type, "Basic")) {
        if ((res = ap_get_basic_auth_pw(r, &password))) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          APLOGNO(02517) "%s: couldn't retrieve basic auth "
                          "password", fn);
            if (dconf->require_basic_auth) {
                return res;
            }
            password = NULL;
        }
    }

    conf = apr_hash_get(fcgi_authn_providers, prov, APR_HASH_KEY_STRING);
    if (!conf) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      APLOGNO(02518) "%s: can't find config for provider %s",
                      fn, prov);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (APLOGrdebug(r)) {
        log_provider_info(conf, r);
    }

    req_rsp(r, conf, password, AP_FCGI_APACHE_ROLE_AUTHENTICATOR_STR,
            rspbuf, &rspbuflen);

    if (r->status == HTTP_OK) {
        if (dconf->user_expr) {
            const char *err;
            const char *user = ap_expr_str_exec(r, dconf->user_expr,
                                                &err);
            if (user && strlen(user)) {
                r->user = apr_pstrdup(r->pool, user);
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              APLOGNO(02519) "%s: Setting user to '%s'",
                              fn, r->user);
            }
            else if (user && dconf->default_user) {
                r->user = apr_pstrdup(r->pool, dconf->default_user);
            }
            else if (user) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              APLOGNO(02520) "%s: Failure extracting user "
                              "after calling authorizer: user expression "
                              "yielded empty string (variable not set?)",
                              fn);
                r->status = HTTP_INTERNAL_SERVER_ERROR;
            }
            else {
                /* unexpected error, not even an empty string was returned */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              APLOGNO(02521) "%s: Failure extracting user "
                              "after calling authorizer: %s",
                              fn, err);
                r->status = HTTP_INTERNAL_SERVER_ERROR;
            }
        }
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
    }
    else {
        /* From the spec:
         *   For Authorizer response status values other than "200" (OK), the 
         *   Web server denies access and sends the response status, headers,
         *   and content back to the HTTP client.
         * But:
         *   This only makes sense if this authorizer is authoritative.
         */
        if (rspbuflen > 0 && !dconf->authoritative) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          APLOGNO(02522) "%s: Ignoring response body from non-"
                          "authoritative authorizer", fn);
        }
        else if (rspbuflen > 0) {
            if (rspbuflen == sizeof rspbuf - 1) {
                /* apr_brigade_flatten() interface :( */
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              APLOGNO(02523) "%s: possible overflow handling "
                              "response body", fn);
            }
            rspbuf[rspbuflen] = '\0'; /* we reserved an extra byte for '\0' */
            ap_custom_response(r, r->status, rspbuf); /* API makes a copy */
        }
    }

    return r->status == HTTP_OK ? 
        OK : dconf->authoritative ? r->status : DECLINED;
}