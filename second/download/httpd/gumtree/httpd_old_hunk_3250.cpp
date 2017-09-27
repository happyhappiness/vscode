            *result = dc;
            break;
        }
        else {
            if (!APR_STATUS_IS_ENOENT(status)
                && !APR_STATUS_IS_ENOTDIR(status)) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, status, r,
                              "%s pcfg_openfile: unable to check htaccess file, "
                              "ensure it is readable",
                              filename);
                apr_table_setn(r->notes, "error-notes",
                               "Server unable to read htaccess file, denying "
                               "access to be safe");
                return HTTP_FORBIDDEN;
            }
        }
