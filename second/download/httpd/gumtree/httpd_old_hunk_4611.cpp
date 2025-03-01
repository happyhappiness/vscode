    if (!worker->cp) {
        rv = ap_proxy_initialize_worker(worker, ctx->s, ctx->p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ctx->s, APLOGNO(03250) "Cannot init worker");
            return rv;
        }
        rv = (hc_determine_connection(ctx, worker) == OK ? APR_SUCCESS : APR_EGENERAL);
    }
    return rv;
}

static apr_status_t backend_cleanup(const char *proxy_function, proxy_conn_rec *backend,
                                    server_rec *s, int status)
