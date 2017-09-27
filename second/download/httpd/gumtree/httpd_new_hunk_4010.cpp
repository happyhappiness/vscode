    return h2_upgrade > 0 || (h2_upgrade < 0 && !h2_h2_is_tls(c));
}

/*******************************************************************************
 * Register various hooks
 */
static const char* const mod_ssl[]        = { "mod_ssl.c", NULL};
static const char* const mod_reqtimeout[] = { "mod_reqtimeout.c", NULL};

void h2_h2_register_hooks(void)
{
    /* Our main processing needs to run quite late. Definitely after mod_ssl,
     * as we need its connection filters, but also before reqtimeout as its
     * method of timeouts is specific to HTTP/1.1 (as of now).
     * The core HTTP/1 processing run as REALLY_LAST, so we will have
     * a chance to take over before it.
     */
    ap_hook_process_connection(h2_h2_process_conn, 
                               mod_ssl, mod_reqtimeout, APR_HOOK_LAST);
    
    /* One last chance to properly say goodbye if we have not done so
     * already. */
    ap_hook_pre_close_connection(h2_h2_pre_close_conn, NULL, mod_ssl, APR_HOOK_LAST);

    /* With "H2SerializeHeaders On", we install the filter in this hook
     * that parses the response. This needs to happen before any other post
     * read function terminates the request with an error. Otherwise we will
     * never see the response.
     */
    ap_hook_post_read_request(h2_h2_post_read_req, NULL, NULL, APR_HOOK_REALLY_FIRST);
}

int h2_h2_process_conn(conn_rec* c)
{
    apr_status_t status;
    h2_ctx *ctx;
    
    if (c->master) {
        return DECLINED;
    }
    
    ctx = h2_ctx_get(c, 0);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn");
    if (h2_ctx_is_task(ctx)) {
        /* our stream pseudo connection */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, "h2_h2, task, declined");
        return DECLINED;
    }
    
    if (!ctx && c->keepalives == 0) {
        const char *proto = ap_get_protocol(c);
        
        if (APLOGctrace1(c)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn, "
                          "new connection using protocol '%s', direct=%d, "
                          "tls acceptable=%d", proto, h2_allows_h2_direct(c), 
                          h2_is_acceptable_connection(c, 1));
        }
        
        if (!strcmp(AP_PROTOCOL_HTTP1, proto)
            && h2_allows_h2_direct(c) 
            && h2_is_acceptable_connection(c, 1)) {
            /* Fresh connection still is on http/1.1 and H2Direct is enabled. 
             * Otherwise connection is in a fully acceptable state.
             * -> peek at the first 24 incoming bytes
             */
            apr_bucket_brigade *temp;
            char *s = NULL;
            apr_size_t slen;
            
            temp = apr_brigade_create(c->pool, c->bucket_alloc);
            status = ap_get_brigade(c->input_filters, temp,
                                    AP_MODE_SPECULATIVE, APR_BLOCK_READ, 24);
            
            if (status != APR_SUCCESS) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03054)
                              "h2_h2, error reading 24 bytes speculative");
                apr_brigade_destroy(temp);
                return DECLINED;
            }
            
            apr_brigade_pflatten(temp, &s, &slen, c->pool);
            if ((slen >= 24) && !memcmp(H2_MAGIC_TOKEN, s, 24)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                              "h2_h2, direct mode detected");
                if (!ctx) {
                    ctx = h2_ctx_get(c, 1);
                }
                h2_ctx_protocol_set(ctx, h2_h2_is_tls(c)? "h2" : "h2c");
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                              "h2_h2, not detected in %d bytes: %s", 
                              (int)slen, s);
            }
            
            apr_brigade_destroy(temp);
        }
    }

    if (ctx) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "process_conn");
        if (!h2_ctx_session_get(ctx)) {
            status = h2_conn_setup(ctx, c, NULL);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c, "conn_setup");
            if (status != APR_SUCCESS) {
                return status;
            }
        }
        return h2_conn_run(ctx, c);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, declined");
    return DECLINED;
}

static int h2_h2_pre_close_conn(conn_rec *c)
{
    h2_ctx *ctx;

    /* slave connection? */
    if (c->master) {
        return DECLINED;
    }

    ctx = h2_ctx_get(c, 0);
    if (ctx) {
        /* If the session has been closed correctly already, we will not
         * fiond a h2_ctx here. The presence indicates that the session
         * is still ongoing. */
        return h2_conn_pre_close(ctx, c);
    }
    return DECLINED;
}

static int h2_h2_post_read_req(request_rec *r)
{
    /* slave connection? */
    if (r->connection->master) {
        h2_ctx *ctx = h2_ctx_rget(r);
        struct h2_task *task = h2_ctx_get_task(ctx);
        /* This hook will get called twice on internal redirects. Take care
         * that we manipulate filters only once. */
        /* our slave connection? */
        if (task && !task->filters_set) {
            ap_filter_t *f;
            
            /* setup the correct output filters to process the response
             * on the proper mod_http2 way. */
            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "adding task output filter");
            if (task->ser_headers) {
                ap_add_output_filter("H1_TO_H2_RESP", task, r, r->connection);
            }
            else {
                /* replace the core http filter that formats response headers
                 * in HTTP/1 with our own that collects status and headers */
                ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
                ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
            }
            
            /* trailers processing. Incoming trailers are added to this
             * request via our h2 input filter, outgoing trailers
             * in a special h2 out filter. */
            for (f = r->input_filters; f; f = f->next) {
                if (!strcmp("H2_TO_H1", f->frec->name)) {
                    f->r = r;
                    break;
                }
            }
            ap_add_output_filter("H2_TRAILERS", task, r, r->connection);
            task->filters_set = 1;
        }
    }
    return DECLINED;
}

