ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01583)
                  "Range: %s | %s (%d : %d : %"APR_OFF_T_FMT")",
                  it, r->range, *overlaps, *reversals, clength);