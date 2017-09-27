     * do not modify add_te_chunked's logic
     */
    if (old_te_val && strcmp(old_te_val, "chunked") != 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "proxy: %s Transfer-Encoding is not supported",
                     old_te_val);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (old_cl_val && old_te_val) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_ENOTIMPL, r->server,
                     "proxy: client %s (%s) requested Transfer-Encoding "
                     "chunked body with Content-Length (C-L ignored)",
