            (*hooks->close_lockdb)(lockdb);
        }

        if (err != NULL) {
            /* ### don't log an error. return err. add higher-level desc. */

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00623)
                          "Failed to query lock-null status for %s",
                          r->filename);

            return DAV_RESOURCE_ERROR;
        }

