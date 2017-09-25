     *
     * !! BUT ALL THIS IS STILL NOT RE-IMPLEMENTED FOR APACHE 2.0 !!
     */
    if (renegotiate && !renegotiate_quick && (r->method_number == M_POST)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "SSL Re-negotiation in conjunction "
                     "with POST method not supported! "
                     "hint: try SSLOptions +OptRenegotiate");

        return HTTP_METHOD_NOT_ALLOWED;
    }

    /*
