
        if (!conf->ignorecachecontrol) {
            /* We're not allowed to serve a cached copy */
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                    "Incoming request is asking for a no-store version of "
                    "%s, but we have been configured to ignore it and serve "
                    "cached content anyway", r->unparsed_uri);
        }
    }

