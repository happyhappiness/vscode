ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02650)
                              "Inflated content ratio is larger than the "
                              "configured limit %i by %i time(s)",
                              dc->ratio_limit, dc->ratio_burst);