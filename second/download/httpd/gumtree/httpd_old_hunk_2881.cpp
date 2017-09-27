        additional = apr_time_from_sec(additional_sec);
        break;
    default:
        /* expecting the add_* routines to be case-hardened this
         * is just a reminder that module is beta
         */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    "internal error: bad expires code: %s", r->filename);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    expires = base + additional;
    if (expires < r->request_time) {
