            else {
                va_list ap;
                const char *res;
                va_start(ap, fmt);
                res = apr_pvsprintf(r->pool, fmt, ap);
                va_end(ap);
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(03158)
                              "%s", res);
            }
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        return AP_FILTER_ERROR;
    }
    return OK;
