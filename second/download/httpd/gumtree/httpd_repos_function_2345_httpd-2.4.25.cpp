static void stream_input_consumed(void *ctx, 
                                  h2_bucket_beam *beam, apr_off_t length)
{
    h2_mplx *m = ctx;
    if (m->input_consumed && length) {
        m->input_consumed(m->input_consumed_ctx, beam->id, length);
    }
}