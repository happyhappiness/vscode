static int report_consumption(h2_bucket_beam *beam, h2_beam_lock *pbl)
{
    int rv = 0;
    apr_off_t len = beam->received_bytes - beam->cons_bytes_reported;
    h2_beam_io_callback *cb = beam->cons_io_cb;
     
    if (len > 0) {
        if (cb) {
            void *ctx = beam->cons_ctx;
            
            if (pbl) leave_yellow(beam, pbl);
            cb(ctx, beam, len);
            if (pbl) enter_yellow(beam, pbl);
            rv = 1;
        }
        beam->cons_bytes_reported += len;
    }
    return rv;
}