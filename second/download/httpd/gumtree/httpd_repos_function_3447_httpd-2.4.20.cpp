static authz_status all_check_authorization(request_rec *r,
                                            const char *require_line,
                                            const void *parsed_require_line)
{
    if (parsed_require_line) {
        return AUTHZ_GRANTED;
    }
    return AUTHZ_DENIED;
}