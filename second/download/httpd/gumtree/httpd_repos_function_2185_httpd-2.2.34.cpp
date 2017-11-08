static int table_do_fn_check_lengths(void *r_, const char *key,
                                     const char *value)
{
    request_rec *r = r_;
    if (value == NULL || r->server->limit_req_fieldsize >= strlen(value) )
        return 1;

    r->status = HTTP_BAD_REQUEST;
    apr_table_setn(r->notes, "error-notes",
                   "Size of a request header field exceeds server limit.");
    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "Request "
                  "header exceeds LimitRequestFieldSize after merging: %.*s",
                  field_name_len(key), key);
    return 0;
}