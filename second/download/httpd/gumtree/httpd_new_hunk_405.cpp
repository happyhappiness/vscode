            if (errmsg == NULL)
                errmsg = ap_walk_config(temptree, &parms, dc);

            ap_cfg_closefile(f);

            if (errmsg) {
                ap_log_rerror(APLOG_MARK, APLOG_ALERT, 0, r,
                              "%s: %s", filename, errmsg);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            *result = dc;
            break;
