
    result = ap_run_handler(r);

    r->handler = old_handler;

    if (result == DECLINED && r->handler && r->filename) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
            "handler \"%s\" not found for: %s", r->handler, r->filename);
    }

    return result == DECLINED ? HTTP_INTERNAL_SERVER_ERROR : result;
}

