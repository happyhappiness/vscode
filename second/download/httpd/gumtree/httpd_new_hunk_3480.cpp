    else
        r->proto_num = HTTP_VERSION(1, 0);

    return 1;
}

static int table_do_fn_check_lengths(void *r_, const char *key,
                                     const char *value)
{
    request_rec *r = r_;
    if (value == NULL || r->server->limit_req_fieldsize >= strlen(value) )
        return 1;

    r->status = HTTP_BAD_REQUEST;
    apr_table_setn(r->notes, "error-notes",
                   apr_pstrcat(r->pool, "Size of a request header field "
                               "after merging exceeds server limit.<br />"
                               "\n<pre>\n",
                               ap_escape_html(r->pool, key),
                               "</pre>\n", NULL));
    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00560) "Request header "
                  "exceeds LimitRequestFieldSize after merging: %s", key);
    return 0;
}

/* get the length of the field name for logging, but no more than 80 bytes */
#define LOG_NAME_MAX_LEN 80
static int field_name_len(const char *field)
{
    const char *end = ap_strchr_c(field, ':');
    if (end == NULL || end - field > LOG_NAME_MAX_LEN)
        return LOG_NAME_MAX_LEN;
    return end - field;
}

AP_DECLARE(void) ap_get_mime_headers_core(request_rec *r, apr_bucket_brigade *bb)
{
    char *last_field = NULL;
    apr_size_t last_len = 0;
    apr_size_t alloc_len = 0;
    char *field;
