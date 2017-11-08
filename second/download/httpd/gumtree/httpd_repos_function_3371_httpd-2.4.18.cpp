static apr_status_t recv_data(const fcgi_provider_conf *conf,
                              request_rec *r,
                              apr_socket_t *s,
                              char *buf,
                              apr_size_t *buflen)
{
    apr_status_t rv;

    rv = apr_socket_recv(s, buf, buflen);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      APLOGNO(02497) "Couldn't read from backend %s",
                      conf->backend);
        return rv;
    }

#if AP_MODULE_MAGIC_AT_LEAST(20130702,2) 
    ap_log_rdata(APLOG_MARK, APLOG_TRACE5, r, "FastCGI data received",
                 buf, *buflen, AP_LOG_DATA_SHOW_OFFSET);
#endif
    return APR_SUCCESS;
}