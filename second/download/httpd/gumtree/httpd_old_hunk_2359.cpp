    if (status == DECLINED) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      "configuration error:  couldn't %s: %s", phase, r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    else {
        return status;
    }
}

/* This is the master logic for processing requests.  Do NOT duplicate
 * this logic elsewhere, or the security model will be broken by future
