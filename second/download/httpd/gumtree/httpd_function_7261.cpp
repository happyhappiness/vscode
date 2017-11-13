static int authenticate_basic_fake(request_rec *r)
{
    const char *auth_line, *user, *pass, *err;
    auth_basic_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &auth_basic_module);

    if (!conf->fakeuser) {
        return DECLINED;
    }

    user = ap_expr_str_exec(r, conf->fakeuser, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02455)
                      "AuthBasicFake: could not evaluate user expression for URI '%s': %s", r->uri, err);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (!user || !*user) {
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02458)
                      "AuthBasicFake: empty username expression for URI '%s', ignoring", r->uri);

        apr_table_unset(r->headers_in, "Authorization");

        return DECLINED;
    }

    pass = ap_expr_str_exec(r, conf->fakepass, &err);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02456)
                      "AuthBasicFake: could not evaluate password expression for URI '%s': %s", r->uri, err);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (!pass || !*pass) {
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02459)
                      "AuthBasicFake: empty password expression for URI '%s', ignoring", r->uri);

        apr_table_unset(r->headers_in, "Authorization");

        return DECLINED;
    }

    auth_line = apr_pstrcat(r->pool, "Basic ",
                            ap_pbase64encode(r->pool,
                                             apr_pstrcat(r->pool, user,
                                                         ":", pass, NULL)),
                            NULL);
    apr_table_setn(r->headers_in, "Authorization", auth_line);

    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02457)
                  "AuthBasicFake: \"Authorization: %s\"",
                  auth_line);

    return OK;
}