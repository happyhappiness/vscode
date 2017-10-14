static int authenticate_form_logout_handler(request_rec * r)
{
    auth_form_config_rec *conf;
    const char *err;

    if (strcmp(r->handler, FORM_LOGOUT_HANDLER)) {
        return DECLINED;
    }

    conf = ap_get_module_config(r->per_dir_config, &auth_form_module);

    /* remove the username and password, effectively logging the user out */
    set_session_auth(r, NULL, NULL, NULL);

    /*
     * make sure the logout page is never cached - otherwise the logout won't
     * work!
     */
    apr_table_addn(r->headers_out, "Cache-Control", "no-store");
    apr_table_addn(r->err_headers_out, "Cache-Control", "no-store");

    /* if set, internal redirect to the logout page */
    if (conf->logout) {
        const char *logout = ap_expr_str_exec(r,
                conf->logout, &err);
        if (!err) {
            apr_table_addn(r->headers_out, "Location", logout);
            return HTTP_TEMPORARY_REDIRECT;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02343)
                          "Can't evaluate logout expression: %s", err);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return HTTP_OK;

}