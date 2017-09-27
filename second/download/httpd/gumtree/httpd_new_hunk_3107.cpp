            if (ret != APR_SUCCESS) {
                return ret;
            }
            return OK;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01865)
               "peruser sessions can only be saved if a user is logged in, "
                          "session not saved: %s", r->uri);
        }
    }

    return DECLINED;
