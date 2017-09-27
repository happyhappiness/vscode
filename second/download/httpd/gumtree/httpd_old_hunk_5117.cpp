            *cp++ = apr_toupper(c);
        }
        else if (c == '-') {
            *cp++ = '_';
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                          "Not exporting header with invalid name as envvar: %s",
                          ap_escape_logitem(r->pool, w));
            return NULL;
        }
    }
    *cp = 0;

    return res;
