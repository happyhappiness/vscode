static void check_data_for(h2_mplx *m, h2_stream *stream, int lock)
{
    if (h2_ififo_push(m->readyq, stream->id) == APR_SUCCESS) {
        apr_atomic_set32(&m->event_pending, 1);
        H2_MPLX_ENTER_MAYBE(m, lock);
        if (m->added_output) {
            apr_thread_cond_signal(m->added_output);
        }
        H2_MPLX_LEAVE_MAYBE(m, lock);
    }
}