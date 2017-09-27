                 */
                thisinfo.filetype = APR_NOFILE;
                break;
            }
            else if (APR_STATUS_IS_EACCES(rv)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "access to %s denied (filesystem path '%s') "
                              "because search permissions are missing on a "
                              "component of the path", r->uri, r->filename);
                return r->status = HTTP_FORBIDDEN;
            }
            else if ((rv != APR_SUCCESS && rv != APR_INCOMPLETE)
                     || !(thisinfo.valid & APR_FINFO_TYPE)) {
                /* If we hit ENOTDIR, we must have over-optimized, deny
                 * rather than assume not found.
                 */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "access to %s failed (filesystem path '%s')", 
                              r->uri, r->filename);
                return r->status = HTTP_FORBIDDEN;
            }

            /* Fix up the path now if we have a name, and they don't agree
             */
            if ((thisinfo.valid & APR_FINFO_NAME)
