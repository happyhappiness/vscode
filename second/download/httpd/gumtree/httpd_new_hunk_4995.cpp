    apr_bucket_alloc_t *bucket_alloc = c->bucket_alloc;
    apr_bucket_brigade *header_brigade;
    apr_bucket_brigade *input_brigade;
    apr_bucket_brigade *temp_brigade;
    apr_bucket *e;
    char *buf;
    apr_status_t status;
    enum rb_methods {RB_INIT, RB_STREAM_CL, RB_STREAM_CHUNKED, RB_SPOOL_CL};
    enum rb_methods rb_method = RB_INIT;
    char *old_cl_val = NULL;
    char *old_te_val = NULL;
    apr_off_t bytes_read = 0;
    apr_off_t bytes;
    int force10, rv;
    conn_rec *origin = p_conn->connection;

    if (apr_table_get(r->subprocess_env, "force-proxy-request-1.0")) {
        if (r->expecting_100) {
            return HTTP_EXPECTATION_FAILED;
        }
        force10 = 1;
    } else {
        force10 = 0;
    }

    header_brigade = apr_brigade_create(p, origin->bucket_alloc);
    rv = ap_proxy_create_hdrbrgd(p, header_brigade, r, p_conn,
                                 worker, conf, uri, url, server_portstr,
                                 &old_cl_val, &old_te_val);
    if (rv != OK) {
        return rv;
    }

    /* We have headers, let's figure out our request body... */
    input_brigade = apr_brigade_create(p, bucket_alloc);

    /* sub-requests never use keepalives, and mustn't pass request bodies.
