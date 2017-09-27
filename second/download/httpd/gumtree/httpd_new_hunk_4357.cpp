    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
                  "h2_mplx(%ld-%d): can_beam_file denied on %s", 
                  m->id, beam->id, beam->tag);
    return 0;
}

static void have_out_data_for(h2_mplx *m, h2_stream *stream, int response);
static void task_destroy(h2_mplx *m, h2_task *task, int called_from_master);

static void check_tx_reservation(h2_mplx *m) 
{
    if (m->tx_handles_reserved <= 0) {
        m->tx_handles_reserved += h2_workers_tx_reserve(m->workers, 
