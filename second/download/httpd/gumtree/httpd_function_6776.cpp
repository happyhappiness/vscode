static void task_destroy(h2_mplx *m, h2_task *task, int called_from_master)
{
    conn_rec *slave = NULL;
    int reuse_slave = 0;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                  "h2_task(%s): destroy", task->id);
    if (called_from_master) {
        /* Process outstanding events before destruction */
        h2_stream *stream = h2_ihash_get(m->streams, task->stream_id);
        if (stream) {
            input_consumed_signal(m, stream);
        }
    }
    
    h2_beam_on_produced(task->output.beam, NULL, NULL);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, 
                  APLOGNO(03385) "h2_task(%s): destroy "
                  "output beam empty=%d, holds proxies=%d", 
                  task->id,
                  h2_beam_empty(task->output.beam),
                  h2_beam_holds_proxies(task->output.beam));
    
    slave = task->c;
    reuse_slave = ((m->spare_slaves->nelts < m->spare_slaves->nalloc)
                   && !task->rst_error);
    
    h2_ihash_remove(m->tasks, task->stream_id);
    h2_ihash_remove(m->redo_tasks, task->stream_id);
    h2_task_destroy(task);

    if (slave) {
        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
        }
        else {
            slave->sbh = NULL;
            h2_slave_destroy(slave);
        }
    }
    
    check_tx_free(m);
}