struct check_header_ctx {
    request_rec *r;
    int strict;
};

/* check a single header, to be used with apr_table_do() */
static int check_header(struct check_header_ctx *ctx,
                        const char *name, const char **val)
{
    const char *pos, *end;
    char *dst = NULL;

    if (name[0] == '\0') {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02428)
                      "Empty response header name, aborting request");
        return 0;
    }

    if (ctx->strict) { 
        end = ap_scan_http_token(name);
    }
    else {
        end = ap_scan_vchar_obstext(name);
    }
    if (*end) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02429)
                      "Response header name '%s' contains invalid "
                      "characters, aborting request",
                      name);
        return 0;
    }

    for (pos = *val; *pos; pos = end) {
        end = ap_scan_http_field_content(pos);
        if (*end) {
            if (end[0] != CR || end[1] != LF || (end[2] != ' ' &&
                                                 end[2] != '\t')) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02430)
                              "Response header '%s' value of '%s' contains "
                              "invalid characters, aborting request",
                              name, pos);
                return 0;
            }
            if (!dst) {
                *val = dst = apr_palloc(ctx->r->pool, strlen(*val) + 1);
            }
        }
        if (dst) {
            memcpy(dst, pos, end - pos);
            dst += end - pos;
            if (*end) {
                /* skip folding and replace with a single space */
                end += 3 + strspn(end + 3, "\t ");
                *dst++ = ' ';
            }
        }
    }
    if (dst) {
        *dst = '\0';
    }
    return 1;
}

static int check_headers_table(apr_table_t *t, struct check_header_ctx *ctx)
{
    const apr_array_header_t *headers = apr_table_elts(t);
    apr_table_entry_t *header;
    int i;

    for (i = 0; i < headers->nelts; ++i) {
        header = &APR_ARRAY_IDX(headers, i, apr_table_entry_t);
        if (!header->key) {
            continue;
        }
        if (!check_header(ctx, header->key, (const char **)&header->val)) {
            return 0;
        }
    }
    return 1;
}

/**
 * Check headers for HTTP conformance
