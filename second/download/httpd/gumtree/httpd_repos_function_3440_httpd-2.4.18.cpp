static int authenticate_form_login_handler(request_rec * r)
{
    auth_form_config_rec *conf;
    const char *err;

    const char *sent_user = NULL, *sent_pw = NULL, *sent_loc = NULL;
    int rv;

    if (strcmp(r->handler, FORM_LOGIN_HANDLER)) {
        return DECLINED;
    }

    if (r->method_number != M_POST) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01811)
          "the " FORM_LOGIN_HANDLER " only supports the POST method for %s",
                      r->uri);
        return HTTP_METHOD_NOT_ALLOWED;
    }

    conf = ap_get_module_config(r->per_dir_config, &auth_form_module);

    rv = get_form_auth(r, conf->username, conf->password, conf->location,
                       NULL, NULL, NULL,
                       &sent_user, &sent_pw, &sent_loc,
                       NULL, NULL, NULL, conf);
    if (OK == rv) {
        rv = check_authn(r, sent_user, sent_pw);
        if (OK == rv) {
            set_session_auth(r, sent_user, sent_pw, conf->site);
            if (sent_loc) {
                apr_table_set(r->headers_out, "Location", sent_loc);
                return HTTP_MOVED_TEMPORARILY;
            }
            if (conf->loginsuccess) {
                const char *loginsuccess = ap_expr_str_exec(r,
                        conf->loginsuccess, &err);
                if (!err) {
                    apr_table_set(r->headers_out, "Location", loginsuccess);
                    return HTTP_MOVED_TEMPORARILY;
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02341)
                                  "Can't evaluate login success expression: %s", err);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }
            }
            return HTTP_OK;
        }
    }

    /* did we prefer to be redirected to the login page on failure instead? */
    if (HTTP_UNAUTHORIZED == rv && conf->loginrequired) {
        const char *loginrequired = ap_expr_str_exec(r,
                conf->loginrequired, &err);
        if (!err) {
            apr_table_set(r->headers_out, "Location", loginrequired);
            return HTTP_MOVED_TEMPORARILY;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02342)
                          "Can't evaluate login required expression: %s", err);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return rv;

}