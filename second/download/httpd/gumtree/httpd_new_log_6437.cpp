ap_log_cerror(APLOG_MARK, lvl, 0, c, "bb_dump(%ld-%d): %s", 
                      c->id, s->id, len? buffer : line);