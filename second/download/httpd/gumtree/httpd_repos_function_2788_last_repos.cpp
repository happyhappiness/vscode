void h2_beam_on_consumed(h2_bucket_beam *beam, 
                         h2_beam_ev_callback *ev_cb,
                         h2_beam_io_callback *io_cb, void *ctx)
{
    h2_beam_lock bl;
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->cons_ev_cb = ev_cb;
        beam->cons_io_cb = io_cb;
        beam->cons_ctx = ctx;
        leave_yellow(beam, &bl);
    }
}