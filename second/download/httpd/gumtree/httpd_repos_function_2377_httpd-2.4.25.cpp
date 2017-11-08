static h2_task *next_stream_task(h2_mplx *m)
{
    h2_task *task = NULL;
    h2_stream *stream;
    int sid;
    while (!m->aborted && !task  && (m->workers_busy < m->workers_limit)
           && (sid = h2_iq_shift(m->q)) > 0) {
        
        stream = h2_ihash_get(m->streams, sid);
        if (stream) {
            conn_rec *slave, **pslave;
            int new_conn = 0;

            pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
            if (pslave) {
                slave = *pslave;
            }
            else {
                slave = h2_slave_create(m->c, stream->id, m->pool);
                new_conn = 1;
            }
            
            slave->sbh = m->c->sbh;
            slave->aborted = 0;
            task = h2_task_create(slave, stream->id, stream->request, 
                                  stream->input, stream->output, m);
            h2_ihash_add(m->tasks, task);
            
            m->c->keepalives++;
            apr_table_setn(slave->notes, H2_TASK_ID_NOTE, task->id);
            if (new_conn) {
                h2_slave_run_pre_connection(slave, ap_get_conn_socket(slave));
            }
            stream->started = 1;
            stream->can_be_cleaned = 0;
            task->worker_started = 1;
            task->started_at = apr_time_now();
            if (sid > m->max_stream_started) {
                m->max_stream_started = sid;
            }

            h2_beam_timeout_set(stream->input, m->stream_timeout);
            h2_beam_on_consumed(stream->input, stream_input_consumed, m);
            h2_beam_on_file_beam(stream->input, can_beam_file, m);
            h2_beam_mutex_set(stream->input, beam_enter, task->cond, m);
            
            h2_beam_buffer_size_set(stream->output, m->stream_max_mem);
            h2_beam_timeout_set(stream->output, m->stream_timeout);
            ++m->workers_busy;
        }
    }
    return task;
}