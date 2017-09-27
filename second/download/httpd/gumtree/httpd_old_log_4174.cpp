ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                    MODNAME ": invalid m->type (%d) in mprint().",
                    m->type);