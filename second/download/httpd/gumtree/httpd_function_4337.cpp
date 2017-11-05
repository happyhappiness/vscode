static char *get_line(apr_bucket_brigade *bbout, apr_bucket_brigade *bbin,
                      conn_rec *c, apr_pool_t *p)
{
    apr_status_t rv;
    apr_size_t len;
    char *line;

    apr_brigade_cleanup(bbout);

    rv = apr_brigade_split_line(bbout, bbin, APR_BLOCK_READ, 8192);
    if (rv) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                      "failed reading line from OCSP server");
        return NULL;
    }
    
    rv = apr_brigade_pflatten(bbout, &line, &len, p);
    if (rv) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                      "failed reading line from OCSP server");
        return NULL;
    }

    if (len && line[len-1] != APR_ASCII_LF) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c,
                      "response header line too long from OCSP server");
        return NULL;
    }

    line[len-1] = '\0';
    if (len > 1 && line[len-2] == APR_ASCII_CR) {
        line[len-2] = '\0';
    }

    return line;
}