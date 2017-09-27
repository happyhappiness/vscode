struct check_header_ctx {
    request_rec *r;
    int strict;
};

/* check a single header, to be used with apr_table_do() */
static int check_header(void *arg, const char *name, const char *val)
{
    struct check_header_ctx *ctx = arg;
    const char *test;

    if (name[0] == '\0') {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02428)
                      "Empty response header name, aborting request");
        return 0;
    }

    if (ctx->strict) { 
        test = ap_scan_http_token(name);
    }
    else {
        test = ap_scan_vchar_obstext(name);
    }
    if (*test) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02429)
                      "Response header name '%s' contains invalid "
                      "characters, aborting request",
                      name);
        return 0;
    }

    test = ap_scan_http_field_content(val);
    if (*test) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02430)
                      "Response header '%s' value of '%s' contains invalid "
                      "characters, aborting request",
                      name, val);
        return 0;
    }
    return 1;
}

/**
 * Check headers for HTTP conformance
