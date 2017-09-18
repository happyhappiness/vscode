            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        const char *pos = lenp;
        int conversion_error = 0;

        while (apr_isdigit(*pos) || apr_isspace(*pos)) {
            ++pos;
        }

        if (*pos == '\0') {
            char *endstr;

            errno = 0;
            r->remaining = strtol(lenp, &endstr, 10);

            if (errno || (endstr && *endstr)) {
                conversion_error = 1; 
            }
        }

        if (*pos != '\0' || conversion_error) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid Content-Length");
            return HTTP_BAD_REQUEST;
        }
    }

