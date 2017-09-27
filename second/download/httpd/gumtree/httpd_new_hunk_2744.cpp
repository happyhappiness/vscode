
            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up.
                 * ap_log_rerror() won't work because the header table used by
                 * ap_log_rerror() hasn't been replicated in the phony r
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server, APLOGNO(01252)
                             "couldn't create child process: %d: %s", rc,
                             apr_filepath_name_get(r->filename));

                procnew->pid = 0; /* no process to clean up */
            }
        }
