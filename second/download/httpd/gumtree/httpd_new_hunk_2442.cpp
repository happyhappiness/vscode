
    /* check to make sure that the request method requires authorization */
    if (!(section->limited & (AP_METHOD_BIT << r->method_number))) {
        auth_result =
            (parent_op == AUTHZ_LOGIC_AND) ? AUTHZ_GRANTED : AUTHZ_NEUTRAL;

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(01625)
                      "authorization result of %s: %s "
                      "(directive limited to other methods)",
                      format_authz_command(r->pool, section),
                      format_authz_result(auth_result));

        return auth_result;
