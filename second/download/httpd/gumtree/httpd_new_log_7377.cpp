ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              APLOGNO(02536) "couldn't encode envvar '%s' in %"
                              APR_SIZE_T_FMT " bytes",
                              elts[next_elem].key, avail_len);