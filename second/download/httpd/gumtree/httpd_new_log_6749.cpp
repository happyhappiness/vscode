ap_log_cerror(APLOG_MARK, level, 0, c, 
                      "beam(%ld-%d,%s,closed=%d,aborted=%d,empty=%d,buf=%ld): %s", 
                      (c->master? c->master->id : c->id), beam->id, beam->tag, 
                      beam->closed, beam->aborted, h2_beam_empty(beam), 
                      (long)h2_beam_get_buffered(beam), msg);