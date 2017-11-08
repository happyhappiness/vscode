static APR_INLINE const char *construct_host_header(request_rec *r,
                                                    int is_v6literal)
{
    struct iovec iov[5];
    apr_size_t nvec = 0;
    /*
     * We cannot use ap_get_server_name/port here, because we must
     * ignore UseCanonicalName/Port.
     */
    if (is_v6literal) {
        iov[nvec].iov_base = "[";
        iov[nvec].iov_len = 1;
        nvec++;
    }
    iov[nvec].iov_base = (void *)r->hostname;
    iov[nvec].iov_len = strlen(r->hostname);
    nvec++;
    if (is_v6literal) {
        iov[nvec].iov_base = "]";
        iov[nvec].iov_len = 1;
        nvec++;
    }
    if (r->parsed_uri.port_str) {
        iov[nvec].iov_base = ":";
        iov[nvec].iov_len = 1;
        nvec++;
        iov[nvec].iov_base = r->parsed_uri.port_str;
        iov[nvec].iov_len = strlen(r->parsed_uri.port_str);
        nvec++;
    }
    return apr_pstrcatv(r->pool, iov, nvec, NULL);
}