static authz_status method_check_authorization(request_rec *r,
                                               const char *require_line,
                                               const void *parsed_require_line)
{
    const apr_int64_t *allowed = parsed_require_line;
    if (*allowed & (AP_METHOD_BIT << r->method_number))
        return AUTHZ_GRANTED;
    else
        return AUTHZ_DENIED;
}