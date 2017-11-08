static h2_task *pop_task(h2_mplx *m)
{
    h2_task *task = NULL;
    int sid;
    while (!m->aborted && !task 
        && (m->workers_busy < m->workers_limit)
        && (sid = h2_iq_shift(m->q)) > 0) {
        h2_io *io = h2_io_set_get(m->stream_ios, sid);
        if (io && io->orphaned) {
            io_destroy(m, io, 0);
            if (m->join_wait) {
                apr_thread_cond_signal(m->join_wait);
            }
        }
        else if (io) {
            conn_rec *slave, **pslave;
            int new_conn = 0;
            
            pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
            if (pslave) {
                slave = *pslave;
            }
            else {
                slave = h2_slave_create(m->c, m->pool, NULL);
                new_conn = 1;
            }
            
            slave->sbh = m->c->sbh;
            io->task = task = h2_task_create(m->id, io->request, slave, m);
            m->c->keepalives++;
            apr_table_setn(slave->notes, H2_TASK_ID_NOTE, task->id);
            if (new_conn) {
                h2_slave_run_pre_connection(slave, ap_get_conn_socket(slave));
            }
            io->worker_started = 1;
            io->started_at = apr_time_now();
            if (sid > m->max_stream_started) {
                m->max_stream_started = sid;
            }
            ++m->workers_busy;
        }
    }
    return task;
}