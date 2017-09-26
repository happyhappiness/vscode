    r->handler = old_handler;

    if (result == DECLINED && r->handler && r->filename) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
            "handler \"%s\" not found for: %s", r->handler, r->filename);
    }

    return result == DECLINED ? HTTP_INTERNAL_SERVER_ERROR : result;
}

AP_DECLARE(int) ap_method_is_limited(cmd_parms *cmd, const char *method)
{
