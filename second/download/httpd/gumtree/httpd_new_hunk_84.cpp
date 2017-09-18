         * mod_info output, hard-coded error documents, etc.
         */
        strcmp(mime_type, DIR_MAGIC_TYPE) &&
#endif
        strncasecmp(mime_type, "message/", 8)) {
        if (dc->debug >= DBGLVL_GORY) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "mime type is %s; no translation selected",
                          mime_type);
        }
        return DECLINED;
    }

    if (dc->debug >= DBGLVL_GORY) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "charset_source: %s charset_default: %s",
                      dc && dc->charset_source ? dc->charset_source : "(none)",
                      dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    /* Get storage for the request data and the output filter context.
