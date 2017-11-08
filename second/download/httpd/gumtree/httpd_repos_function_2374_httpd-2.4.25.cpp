static void have_out_data_for(h2_mplx *m, h2_stream *stream, int response)
{
    ap_assert(m);
    ap_assert(stream);
    h2_iq_append(m->readyq, stream->id);
    if (m->added_output) {
        apr_thread_cond_signal(m->added_output);
    }
}