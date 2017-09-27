        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                      "Request received from client: %s",
                      ap_escape_logitem(r->pool, r->the_request));
    }

    r->request_time = apr_time_now();
    ll = r->the_request;
    r->method = ap_getword_white(r->pool, &ll);

    uri = ap_getword_white(r->pool, &ll);

    if (!*r->method || !*uri) {
        r->status    = HTTP_BAD_REQUEST;
        r->proto_num = HTTP_VERSION(1,0);
        r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
        return 0;
    }

    /* Provide quick information about the request method as soon as known */

    r->method_number = ap_method_number_of(r->method);
    if (r->method_number == M_GET && r->method[0] == 'H') {
        r->header_only = 1;
    }

    ap_parse_uri(r, uri);
    if (r->status != HTTP_OK) {
        r->proto_num = HTTP_VERSION(1,0);
        r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
        return 0;
    }

    if (ll[0]) {
        r->assbackwards = 0;
        pro = ll;
        len = strlen(ll);
    } else {
        r->assbackwards = 1;
        pro = "HTTP/0.9";
        len = 8;
    }
    r->protocol = apr_pstrmemdup(r->pool, pro, len);

    /* Avoid sscanf in the common case */
    if (len == 8
        && pro[0] == 'H' && pro[1] == 'T' && pro[2] == 'T' && pro[3] == 'P'
        && pro[4] == '/' && apr_isdigit(pro[5]) && pro[6] == '.'
        && apr_isdigit(pro[7])) {
        r->proto_num = HTTP_VERSION(pro[5] - '0', pro[7] - '0');
    }
    else if (3 == sscanf(r->protocol, "%4s/%u.%u", http, &major, &minor)
             && (strcasecmp("http", http) == 0)
             && (minor < HTTP_VERSION(1, 0)) ) /* don't allow HTTP/0.1000 */
        r->proto_num = HTTP_VERSION(major, minor);
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
    char *value;
    apr_size_t len;
    int fields_read = 0;
    char *tmp_field;

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), reach the server limit, or we timeout.
     */
    while(1) {
        apr_status_t rv;
        int folded = 0;

        field = NULL;
        rv = ap_rgetline(&field, r->server->limit_req_fieldsize + 2,
                         &len, r, 0, bb);

        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_TIMEUP(rv)) {
                r->status = HTTP_REQUEST_TIME_OUT;
            }
            else {
