ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                  "h2_mplx(%ld-%d): can_beam_file denied on %s", 
                  m->id, beam->id, beam->tag);