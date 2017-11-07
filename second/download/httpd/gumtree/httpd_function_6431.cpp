static int authenticate_form_authn(request_rec * r)
{
    auth_form_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &auth_form_module);
    const char *sent_user = NULL, *sent_pw = NULL, *sent_hash = NULL;
    const char *sent_loc = NULL, *sent_method = "GET", *sent_mimetype = NULL;
    const char *current_auth = NULL;
    const char *err;
    apr_status_t res;
    int rv = HTTP_UNAUTHORIZED;

    /* Are we configured to be Form auth? */
    current_auth = ap_auth_type(r);
    if (!current_auth || strcasecmp(current_auth, "form")) {
        return DECLINED;
    }

    /*
     * XSS security warning: using cookies to store private data only works
     * when the administrator has full control over the source website. When
     * in forward-proxy mode, websites are public by definition, and so can
     * never be secure. Abort the auth attempt in this case.
     */
    if (PROXYREQ_PROXY == r->proxyreq) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, APLOGNO(01809) "form auth cannot be used for proxy "
                      "requests due to XSS risk, access denied: %s", r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* We need an authentication realm. */
    if (!ap_auth_name(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, APLOGNO(01810) "need AuthName: %s", r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    r->ap_auth_type = (char *) current_auth;

    /* try get the username and password from the notes, if present */
    get_notes_auth(r, &sent_user, &sent_pw, &sent_method, &sent_mimetype);
    if (!sent_user || !sent_pw || !*sent_user || !*sent_pw) {

        /* otherwise try get the username and password from a session, if present */
        res = get_session_auth(r, &sent_user, &sent_pw, &sent_hash);

    }
    else {
        res = APR_SUCCESS;
    }

    /* first test whether the site passphrase matches */
    if (APR_SUCCESS == res && sent_user && sent_hash && sent_pw) {
        rv = check_site(r, conf->site, sent_user, sent_hash);
        if (OK == rv) {
            fake_basic_authentication(r, conf, sent_user, sent_pw);
            return OK;
        }
    }

    /* otherwise test for a normal password match */
    if (APR_SUCCESS == res && sent_user && sent_pw) {
        rv = check_authn(r, sent_user, sent_pw);
        if (OK == rv) {
            fake_basic_authentication(r, conf, sent_user, sent_pw);
            return OK;
        }
    }

    /*
     * If we reach this point, the request should fail with access denied,
     * except for one potential scenario:
     *
     * If the request is a POST, and the posted form contains user defined fields
     * for a username and a password, and the username and password are correct,
     * then return the response obtained by a GET to this URL.
     *
     * If an additional user defined location field is present in the form,
     * instead of a GET of the current URL, redirect the browser to the new
     * location.
     *
     * As a further option, if the user defined fields for the type of request,
     * the mime type of the body of the request, and the body of the request
     * itself are present, replace this request with a new request of the given
     * type and with the given body.
     *
     * Otherwise access is denied.
     *
     * Reading the body requires some song and dance, because the input filters
     * are not yet configured. To work around this problem, we create a
     * subrequest and use that to create a sane filter stack we can read the
     * form from.
     *
     * The main request is then capped with a kept_body input filter, which has
     * the effect of guaranteeing the input stack can be safely read a second time.
     *
     */
    if (HTTP_UNAUTHORIZED == rv && r->method_number == M_POST && ap_is_initial_req(r)) {
        request_rec *rr;
        apr_bucket_brigade *sent_body = NULL;

        /* create a subrequest of our current uri */
        rr = ap_sub_req_lookup_uri(r->uri, r, r->input_filters);
        rr->headers_in = r->headers_in;

        /* run the insert_filters hook on the subrequest to ensure a body read can
         * be done properly.
         */
        ap_run_insert_filter(rr);

        /* parse the form by reading the subrequest */
        rv = get_form_auth(rr, conf->username, conf->password, conf->location,
                           conf->method, conf->mimetype, conf->body,
                           &sent_user, &sent_pw, &sent_loc, &sent_method,
                           &sent_mimetype, &sent_body, conf);

        /* make sure any user detected within the subrequest is saved back to
         * the main request.
         */
        r->user = apr_pstrdup(r->pool, rr->user);

        /* we cannot clean up rr at this point, as memory allocated to rr is
         * referenced from the main request. It will be cleaned up when the
         * main request is cleaned up.
         */

        /* insert the kept_body filter on the main request to guarantee the
         * input filter stack cannot be read a second time, optionally inject
         * a saved body if one was specified in the login form.
         */
        if (sent_body && sent_mimetype) {
            apr_table_set(r->headers_in, "Content-Type", sent_mimetype);
            r->kept_body = sent_body;
        }
        else {
            r->kept_body = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        }
        ap_request_insert_filter_fn(r);

        /* did the form ask to change the method? if so, switch in the redirect handler
         * to relaunch this request as the subrequest with the new method. If the
         * form didn't specify a method, the default value GET will force a redirect.
         */
        if (sent_method && strcmp(r->method, sent_method)) {
            r->handler = FORM_REDIRECT_HANDLER;
        }

        /* check the authn in the main request, based on the username found */
        if (OK == rv) {
            rv = check_authn(r, sent_user, sent_pw);
            if (OK == rv) {
                fake_basic_authentication(r, conf, sent_user, sent_pw);
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
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02339)
                                      "Can't evaluate login success expression: %s", err);
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }
                }
            }
        }

    }

    /*
     * did the admin prefer to be redirected to the login page on failure
     * instead?
     */
    if (HTTP_UNAUTHORIZED == rv && conf->loginrequired) {
        const char *loginrequired = ap_expr_str_exec(r,
                conf->loginrequired, &err);
        if (!err) {
            apr_table_set(r->headers_out, "Location", loginrequired);
            return HTTP_MOVED_TEMPORARILY;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02340)
                          "Can't evaluate login required expression: %s", err);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    /* did the user ask to be redirected on login success? */
    if (sent_loc) {
        apr_table_set(r->headers_out, "Location", sent_loc);
        rv = HTTP_MOVED_TEMPORARILY;
    }


    /*
     * potential security issue: if we return a login to the browser, we must
     * send a no-store to make sure a well behaved browser will not try and
     * send the login details a second time if the back button is pressed.
     *
     * if the user has full control over the backend, the
     * AuthCookieDisableNoStore can be used to turn this off.
     */
    if (HTTP_UNAUTHORIZED == rv && !conf->disable_no_store) {
        apr_table_addn(r->headers_out, "Cache-Control", "no-store");
        apr_table_addn(r->err_headers_out, "Cache-Control", "no-store");
    }

    return rv;

}