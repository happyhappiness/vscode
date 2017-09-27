    r->filename = apr_pstrcat(r->pool, "proxy:fcgi://", host, sport, "/",
                              path, NULL);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01060)
                  "set r->filename to %s", r->filename);

    if (apr_table_get(r->subprocess_env, "proxy-fcgi-pathinfo")) {
        r->path_info = apr_pstrcat(r->pool, "/", path, NULL);

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01061)
                      "set r->path_info to %s", r->path_info);
    }

    return OK;
}

/* Wrapper for apr_socket_sendv that handles updating the worker stats. */
