static void stream_done(h2_mplx *m, h2_stream *stream, int rst_error) 
{
    h2_task *task;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                  "h2_stream(%ld-%d): done", m->c->id, stream->id);
    /* Situation: we are, on the master connection, done with processing
     * the stream. Either we have handled it successfully, or the stream
     * was reset by the client or the connection is gone and we are 
     * shutting down the whole session.
     *
     * We possibly have created a task for this stream to be processed
     * on a slave connection. The processing might actually be ongoing
     * right now or has already finished. A finished task waits for its
     * stream to be done. This is the common case.
     * 
     * If the stream had input (e.g. the request had a body), a task
     * may have read, or is still reading buckets from the input beam.
     * This means that the task is referencing memory from the stream's
     * pool (or the master connection bucket alloc). Before we can free
     * the stream pool, we need to make sure that those references are
     * gone. This is what h2_beam_shutdown() on the input waits for.
     *
     * With the input handled, we can tear down that beam and care
     * about the output beam. The stream might still have buffered some
     * buckets read from the output, so we need to get rid of those. That
     * is done by h2_stream_cleanup().
     *
     * Now it is save to destroy the task (if it exists and is finished).
     * 
     * FIXME: we currently destroy the stream, even if the task is still
     * ongoing. This is not ok, since task->request is coming from stream
     * memory. We should either copy it on task creation or wait with the
     * stream destruction until the task is done. 
     */
    h2_iq_remove(m->q, stream->id);
    h2_ihash_remove(m->sready, stream->id);
    h2_ihash_remove(m->sresume, stream->id);
    h2_ihash_remove(m->streams, stream->id);
    if (stream->input) {
        m->tx_handles_reserved += h2_beam_get_files_beamed(stream->input);
        h2_beam_on_consumed(stream->input, NULL, NULL);
        /* Let anyone blocked reading know that there is no more to come */
        h2_beam_abort(stream->input);
        /* Remove mutex after, so that abort still finds cond to signal */
        h2_beam_mutex_set(stream->input, NULL, NULL, NULL);
    }
    h2_stream_cleanup(stream);

    task = h2_ihash_get(m->tasks, stream->id);
    if (task) {
        if (!task->worker_done) {
            /* task still running, cleanup once it is done */
            if (rst_error) {
                h2_task_rst(task, rst_error);
            }
            h2_ihash_add(m->shold, stream);
            return;
        }
        else {
            /* already finished */
            task_destroy(m, task, 0);
        }
    }
    h2_stream_destroy(stream);
}