                /* Soak up all the script output - may save an outright kill */
                while ((*getsfunc)(w, MAX_STRING_LEN - 1, getsfunc_data) > 0) {
                    continue;
                }
            }

            ap_log_rerror(SCRIPT_LOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                          "malformed header from script '%s': Bad header: %.30s",
                          apr_filepath_name_get(r->filename), w);
            return HTTP_INTERNAL_SERVER_ERROR;
        }

