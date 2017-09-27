                           perdir ? perdir : "",
                           perdir ? "] ": "",
                           text);

    AP_REWRITE_LOG((uintptr_t)r, level, r->main ? 0 : 1, (char *)ap_get_server_name(r), logline);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG + level, 0, r, logline);

    return;
}
#endif /* !REWRITELOG_DISABLED */


