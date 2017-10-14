static authz_status validuser_check_authorization(request_rec *r, const char *require_line)
{
    if (!r->user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    return AUTHZ_GRANTED;
}