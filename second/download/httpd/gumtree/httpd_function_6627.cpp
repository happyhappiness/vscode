apr_status_t h2_request_add_trailer(h2_request *req, apr_pool_t *pool,
                                    const char *name, size_t nlen,
                                    const char *value, size_t vlen)
{
    if (!req->trailers) {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool, APLOGNO(03059)
                      "h2_request(%d): unanounced trailers",
                      req->id);
        return APR_EINVAL;
    }
    if (nlen == 0 || name[0] == ':') {
        ap_log_perror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, pool, APLOGNO(03060)
                      "h2_request(%d): pseudo header in trailer",
                      req->id);
        return APR_EINVAL;
    }
    return add_h1_trailer(req, pool, name, nlen, value, vlen);
}