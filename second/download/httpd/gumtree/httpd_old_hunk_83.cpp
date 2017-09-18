    }

    /* If we don't have a full directory configuration, bail out.
     */
    if (!dc->charset_source || !dc->charset_default) {
        if (dc->debug >= DBGLVL_PMC) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                          "incomplete configuration: src %s, dst %s",
                          dc->charset_source ? dc->charset_source : "unspecified",
                          dc->charset_default ? dc->charset_default : "unspecified");
        }
        return DECLINED;
    }
