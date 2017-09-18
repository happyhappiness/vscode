            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        int conversion_error = 0;
        char *endstr;

        errno = 0;
        r->remaining = strtol(lenp, &endstr, 10); /* depend on ANSI */

        /* See comments in ap_http_filter() */
        if (errno || (endstr && *endstr) || (r->remaining < 0)) {
            conversion_error = 1; 
        }

        if (conversion_error) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid Content-Length");
            return HTTP_BAD_REQUEST;
        }
    }

