    char *line;

    apr_brigade_cleanup(bbout);

    rv = apr_brigade_split_line(bbout, bbin, APR_BLOCK_READ, 8192);
    if (rv) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01977)
                      "failed reading line from OCSP server");
        return NULL;
    }

    rv = apr_brigade_pflatten(bbout, &line, &len, p);
    if (rv) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01978)
                      "failed reading line from OCSP server");
        return NULL;
    }

    if (len && line[len-1] != APR_ASCII_LF) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01979)
                      "response header line too long from OCSP server");
        return NULL;
    }

    line[len-1] = '\0';
    if (len > 1 && line[len-2] == APR_ASCII_CR) {
