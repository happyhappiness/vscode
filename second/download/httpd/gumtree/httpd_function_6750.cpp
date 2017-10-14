void h2_beam_log(h2_bucket_beam *beam, conn_rec *c, int level, const char *msg)
{
    if (beam && APLOG_C_IS_LEVEL(c,level)) {
        ap_log_cerror(APLOG_MARK, level, 0, c, 
                      "beam(%ld-%d,%s,closed=%d,aborted=%d,empty=%d,buf=%ld): %s", 
                      (c->master? c->master->id : c->id), beam->id, beam->tag, 
                      beam->closed, beam->aborted, h2_beam_empty(beam), 
                      (long)h2_beam_get_buffered(beam), msg);
    }
}