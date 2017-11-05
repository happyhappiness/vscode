ap_log_cerror(APLOG_MARK, lvl, 0, c, 
                      H2_STRM_MSG(s, "out-buffer(%s)"), len? buffer : "empty");