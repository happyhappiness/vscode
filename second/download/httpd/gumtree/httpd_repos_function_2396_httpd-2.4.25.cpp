int h2_mplx_awaits_data(h2_mplx *m)
{
    apr_status_t status;
    int acquired, waiting = 1;
     
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (h2_ihash_empty(m->streams)) {
            waiting = 0;
        }
        if (h2_iq_empty(m->q) && h2_ihash_empty(m->tasks)) {
            waiting = 0;
        }
        leave_mutex(m, acquired);
    }
    return waiting;
}