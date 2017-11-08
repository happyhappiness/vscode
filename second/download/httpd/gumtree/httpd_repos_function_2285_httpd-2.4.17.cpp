static void have_out_data_for(h2_mplx *m, int stream_id)
{
    (void)stream_id;
    AP_DEBUG_ASSERT(m);
    if (m->added_output) {
        apr_thread_cond_signal(m->added_output);
    }
}