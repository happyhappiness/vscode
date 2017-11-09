static int stream_cancel_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;

    /* disabled input consumed reporting */
    if (stream->input) {
        h2_beam_on_consumed(stream->input, NULL, NULL, NULL);
    }
    /* take over event monitoring */
    h2_stream_set_monitor(stream, NULL);
    /* Reset, should transit to CLOSED state */
    h2_stream_rst(stream, H2_ERR_NO_ERROR);
    /* All connection data has been sent, simulate cleanup */
    h2_stream_dispatch(stream, H2_SEV_EOS_SENT);
    stream_cleanup(m, stream);  
    return 0;
}