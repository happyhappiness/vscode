static void output_produced(void *ctx, h2_bucket_beam *beam, apr_off_t bytes)
{
    h2_stream *stream = ctx;
    h2_mplx *m = stream->session->mplx;
    
    check_data_for(m, stream, 1);
}