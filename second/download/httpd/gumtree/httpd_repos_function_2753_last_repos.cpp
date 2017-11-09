static void report_prod_io(h2_bucket_beam *beam, int force, h2_beam_lock *pbl)
{
    apr_off_t len = beam->sent_bytes - beam->prod_bytes_reported;
    if (force || len > 0) {
        h2_beam_io_callback *cb = beam->prod_io_cb; 
        if (cb) {
            void *ctx = beam->prod_ctx;
            
            leave_yellow(beam, pbl);
            cb(ctx, beam, len);
            enter_yellow(beam, pbl);
        }
        beam->prod_bytes_reported += len;
    }
}