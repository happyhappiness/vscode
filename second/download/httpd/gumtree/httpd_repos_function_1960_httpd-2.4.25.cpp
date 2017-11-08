static apr_status_t backend_cleanup(const char *proxy_function, proxy_conn_rec *backend,
                                    server_rec *s, int status)
{
    if (backend) {
        backend->close = 1;
        ap_proxy_release_connection(proxy_function, backend, s);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03251)
                     "Health check %s Status (%d) for %s.",
                     ap_proxy_show_hcmethod(backend->worker->s->method),
                     status,
                     backend->worker->s->name);
    }
    if (status != OK) {
        return APR_EGENERAL;
    }
    return APR_SUCCESS;
}