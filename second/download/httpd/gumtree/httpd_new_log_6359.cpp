ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                      "h2_mplx(%ld-%d): beaming file %s, tx_avail %d", 
                      m->id, beam->id, beam->tag, m->tx_handles_reserved);