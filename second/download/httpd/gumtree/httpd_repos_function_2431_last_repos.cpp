static void task_destroy(h2_mplx *m, h2_task *task)
{
    conn_rec *slave = NULL;
    int reuse_slave = 0;
    
    slave = task->c;

    if (m->s->keep_alive_max == 0 || slave->keepalives < m->s->keep_alive_max) {
        reuse_slave = ((m->spare_slaves->nelts < (m->limit_active * 3 / 2))
                       && !task->rst_error);
    }
    
    if (slave) {
        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
            h2_beam_log(task->output.beam, m->c, APLOG_DEBUG, 
                        APLOGNO(03385) "h2_task_destroy, reuse slave");    
            h2_task_destroy(task);
            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
        }
        else {
            h2_beam_log(task->output.beam, m->c, APLOG_TRACE1, 
                        "h2_task_destroy, destroy slave");    
            slave->sbh = NULL;
            h2_slave_destroy(slave);
        }
    }
}