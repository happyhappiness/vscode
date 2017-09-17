            return (lenp) ? HTTP_BAD_REQUEST : HTTP_LENGTH_REQUIRED;
        }

        r->read_chunked = 1;
    }
    else if (lenp) {
        const char *pos = lenp;

        while (ap_isdigit(*pos) || ap_isspace(*pos))
            ++pos;
        if (*pos != '\0') {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "Invalid Content-Length %s", lenp);
            return HTTP_BAD_REQUEST;
        }
