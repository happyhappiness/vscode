
    if (frec->ftype < AP_FTYPE_PROTOCOL) {
        if (r) {
            outf = r_filters;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "a content filter was added without a request: %s", frec->name);
            return NULL;
        }
    }
    else if (frec->ftype < AP_FTYPE_CONNECTION) {
        if (r) {
            outf = p_filters;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                         "a protocol filter was added without a request: %s", frec->name);
            return NULL;
        }
    }
    else {
        outf = c_filters;
    }
