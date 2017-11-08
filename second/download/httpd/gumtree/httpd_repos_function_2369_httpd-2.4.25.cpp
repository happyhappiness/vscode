static void output_produced(void *ctx, h2_bucket_beam *beam, apr_off_t bytes)
{
    h2_mplx *m = ctx;
    apr_status_t status;
    h2_stream *stream;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        stream = h2_ihash_get(m->streams, beam->id);
        if (stream) {
            have_out_data_for(m, stream, 0);
        }
        leave_mutex(m, acquired);
    }
}