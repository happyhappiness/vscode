static int can_beam_file(void *ctx, h2_bucket_beam *beam,  apr_file_t *file)
{
    h2_mplx *m = ctx;
    if (m->tx_handles_reserved > 0) {
        --m->tx_handles_reserved;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                      "h2_mplx(%ld-%d): beaming file %s, tx_avail %d", 
                      m->id, beam->id, beam->tag, m->tx_handles_reserved);
        return 1;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                  "h2_mplx(%ld-%d): can_beam_file denied on %s", 
                  m->id, beam->id, beam->tag);
    return 0;
}