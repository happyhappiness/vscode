void h2_beam_on_consumed(h2_bucket_beam *beam, 
                         h2_beam_io_callback *cb, void *ctx)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->consumed_fn = cb;
        beam->consumed_ctx = ctx;
        leave_yellow(beam, &bl);
    }
}