static int hc_read_headers(sctx_t *ctx, request_rec *r)
{
    char buffer[HUGE_STRING_LEN];
    int len;

    len = ap_getline(buffer, sizeof(buffer), r, 1);
    if (len <= 0) {
        return !OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03254)
            "%s", buffer);
    /* for the below, see ap_proxy_http_process_response() */
    if (apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
        int major;
        char keepchar;
        int proxy_status = OK;
        const char *proxy_status_line = NULL;

        major = buffer[5] - '0';
        if ((major != 1) || (len >= sizeof(buffer)-1)) {
            return !OK;
        }

        keepchar = buffer[12];
        buffer[12] = '\0';
        proxy_status = atoi(&buffer[9]);
        if (keepchar != '\0') {
            buffer[12] = keepchar;
        } else {
            buffer[12] = ' ';
            buffer[13] = '\0';
        }
        proxy_status_line = apr_pstrdup(r->pool, &buffer[9]);
        r->status = proxy_status;
        r->status_line = proxy_status_line;
    } else {
        return !OK;
    }
    /* OK, 1st line is OK... scarf in the headers */
    while ((len = ap_getline(buffer, sizeof(buffer), r, 1)) > 0) {
        char *value, *end;
        if (!(value = strchr(buffer, ':'))) {
            return !OK;
        }
        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, ctx->s, "%s", buffer);
        *value = '\0';
        ++value;
        while (apr_isspace(*value))
            ++value;            /* Skip to start of value   */
        for (end = &value[strlen(value)-1]; end > value && apr_isspace(*end); --end)
            *end = '\0';
        apr_table_add(r->headers_out, buffer, value);
    }
    return OK;
}