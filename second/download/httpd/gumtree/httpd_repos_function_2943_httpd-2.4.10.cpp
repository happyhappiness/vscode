static void req_rsp(request_rec *r, const fcgi_provider_conf *conf,
                    const char *password, const char *apache_role,
                    char *rspbuf, apr_size_t *rspbuflen)
{
    const char *fn = "req_rsp";
    apr_pool_t *temp_pool;
    apr_size_t orspbuflen;
    apr_socket_t *s;
    apr_status_t rv;
    apr_table_t *saved_subprocess_env = 
      apr_table_copy(r->pool, r->subprocess_env);

    if (rspbuflen) {
        orspbuflen = *rspbuflen;
        *rspbuflen = 0; /* unless we actually read something */
    }

    apr_pool_create(&temp_pool, r->pool);

    setupenv(r, password, apache_role);

    rv = connect_to_peer(&s, r, conf->backend_addrs,
                         conf->backend, FCGI_IO_TIMEOUT);
    if (rv == APR_SUCCESS) {
        apr_uint16_t request_id = 1;

        rv = send_begin_request(r, conf, s, AP_FCGI_AUTHORIZER, request_id);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          APLOGNO(02511) "%s: Failed writing request to %s",
                          fn, conf->backend);
        }

        if (rv == APR_SUCCESS) {
            rv = send_environment(s, conf, r, request_id, temp_pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              APLOGNO(02512) "%s: Failed writing environment "
                              "to %s", fn, conf->backend);
            }
        }

        /* The responder owns the request body, not the authorizer.
         * Don't even send an empty AP_FCGI_STDIN block.  libfcgi doesn't care,
         * but it wasn't sent to authorizers by mod_fastcgi or mod_fcgi and
         * may be unhandled by the app.  Additionally, the FastCGI spec does
         * not mention FCGI_STDIN in the Authorizer description, though it
         * does describe FCGI_STDIN elsewhere in more general terms than
         * simply a wrapper for the client's request body.
         */

        if (rv == APR_SUCCESS) {
            if (rspbuflen) {
                *rspbuflen = orspbuflen;
            }
            rv = handle_response(conf, r, s, temp_pool, request_id, rspbuf,
                                 rspbuflen);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              APLOGNO(02514) "%s: Failed handling response "
                              "from %s", fn, conf->backend);
            }
        }

        apr_socket_close(s);
    }

    if (rv != APR_SUCCESS) {
        /* some sort of mechanical problem */
        r->status = HTTP_INTERNAL_SERVER_ERROR;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      APLOGNO(02515) "%s: Received HTTP status %d",
                      fn, r->status);
    }

    r->subprocess_env = saved_subprocess_env;

    if (r->status == HTTP_OK) {
        /* An Authorizer application's 200 response may include headers
         * whose names are prefixed with Variable-, and they should be
         * available to subsequent phases via subprocess_env (and yanked
         * from the client response).
         */
        apr_table_t *vars = apr_table_make(temp_pool, /* not used to allocate
                                                       * any values that end up
                                                       * in r->(anything)
                                                       */
                                           10);
        apr_table_do(mod_fcgid_modify_auth_header, vars,
                     r->err_headers_out, NULL);
        apr_table_do(fix_auth_header, r, vars, NULL);
    }

    apr_pool_destroy(temp_pool);
}