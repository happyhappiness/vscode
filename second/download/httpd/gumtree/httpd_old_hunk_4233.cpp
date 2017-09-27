        }
        leave_mutex(m, acquired);
    }
    return status;
}

static h2_io *open_io(h2_mplx *m, int stream_id, const h2_request *request)
{
    apr_pool_t *io_pool;
    h2_io *io;
    
    apr_pool_create(&io_pool, m->pool);
    apr_pool_tag(io_pool, "h2_io");
    io = h2_io_create(stream_id, io_pool, m->bucket_alloc, request);
    h2_io_set_add(m->stream_ios, io);
    
    return io;
}


apr_status_t h2_mplx_process(h2_mplx *m, int stream_id, 
                             const h2_request *req, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int do_registration = 0;
    int acquired;
    
    AP_DEBUG_ASSERT(m);
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            h2_io *io = open_io(m, stream_id, req);
            
            if (!io->request->body) {
                status = h2_io_in_close(io);
            }
            
            m->need_registration = m->need_registration || h2_iq_empty(m->q);
            do_registration = (m->need_registration && m->workers_busy < m->workers_max);
            h2_iq_add(m->q, io->id, cmp, ctx);
            
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                          "h2_mplx(%ld-%d): process", m->c->id, stream_id);
            H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_process");
        }
        leave_mutex(m, acquired);
    }
    if (status == APR_SUCCESS && do_registration) {
        workers_register(m);
    }
    return status;
}

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

