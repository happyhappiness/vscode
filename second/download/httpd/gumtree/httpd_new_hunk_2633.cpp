    if (strcmp(r->handler, DAV_HANDLER_NAME) != 0)
        return DECLINED;

    /* Reject requests with an unescaped hash character, as these may
     * be more destructive than the user intended. */
    if (r->parsed_uri.fragment != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00622)
                     "buggy client used un-escaped hash in Request-URI");
        return dav_error_response(r, HTTP_BAD_REQUEST,
                                  "The request was invalid: the URI included "
                                  "an un-escaped hash character");
    }

