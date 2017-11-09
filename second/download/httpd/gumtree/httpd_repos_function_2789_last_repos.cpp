void h2_beam_on_produced(h2_bucket_beam *beam, 
                         h2_beam_io_callback *io_cb, void *ctx)
{
    h2_beam_lock bl;
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->prod_io_cb = io_cb;
        beam->prod_ctx = ctx;
        leave_yellow(beam, &bl);
    }
}