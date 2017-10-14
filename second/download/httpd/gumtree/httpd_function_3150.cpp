static int authenticate_form_login_handler(request_rec * r)
{

    auth_form_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &auth_form_module);

    const char *sent_user = NULL, *sent_pw = NULL, *sent_loc = NULL;
    int rv;

    if (strcmp(r->handler, FORM_LOGIN_HANDLER)) {
        return DECLINED;
    }

    if (r->method_number != M_POST) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
          "the " FORM_LOGIN_HANDLER " only supports the POST method for %s",
                      r->uri);
        return HTTP_METHOD_NOT_ALLOWED;
    }

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
                apr_table_set(r->headers_out, "Location", conf->loginsuccess);
                return HTTP_MOVED_TEMPORARILY;
            }
            return HTTP_OK;
        }
    }

    /* did we prefer to be redirected to the login page on failure instead? */
    if (HTTP_UNAUTHORIZED == rv && conf->loginrequired) {
        apr_table_set(r->headers_out, "Location", conf->loginrequired);
        return HTTP_MOVED_TEMPORARILY;
    }

    return rv;

}