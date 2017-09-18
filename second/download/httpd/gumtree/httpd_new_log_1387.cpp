ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "mod_rewrite's internal redirect status: %d/%d.",
                  reqc->redirects, reqc->redirect_limit);