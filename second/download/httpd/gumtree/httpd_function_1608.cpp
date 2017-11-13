static int check_header(struct check_header_ctx *ctx,
                        const char *name, const char **val)
{
    const char *pos, *end;
    char *dst = NULL;

    if (name[0] == '\0') {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
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
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r,
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