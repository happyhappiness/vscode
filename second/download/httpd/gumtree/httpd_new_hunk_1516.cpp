                --cp;
        }
        else {
#if defined(EACCES)
            if (errno != EACCES)
#endif
                ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
                            "access to %s failed", r->uri);
            return HTTP_FORBIDDEN;
        }
#else
#error ENOENT || ENOTDIR not defined; please see the
#error comments at this line in the source for a workaround.
        /*
