    do { \
        if (APLOG_C_IS_LEVEL((m)->c,lvl)) \
        h2_util_bb_log((m)->c,(io)->id,lvl,msg,(io)->bbin); \
    } while(0)


/* NULL or the mutex hold by this thread, used for recursive calls
 */
static apr_threadkey_t *thread_lock;

apr_status_t h2_mplx_child_init(apr_pool_t *pool, server_rec *s)
{
    return apr_threadkey_private_create(&thread_lock, NULL, pool);
}

static apr_status_t enter_mutex(h2_mplx *m, int *pacquired)
{
    apr_status_t status;
    void *mutex = NULL;
    
    /* Enter the mutex if this thread already holds the lock or
     * if we can acquire it. Only on the later case do we unlock
     * onleaving the mutex.
     * This allow recursive entering of the mutex from the saem thread,
     * which is what we need in certain situations involving callbacks
     */
    apr_threadkey_private_get(&mutex, thread_lock);
    if (mutex == m->lock) {
        *pacquired = 0;
        return APR_SUCCESS;
    }
        
    status = apr_thread_mutex_lock(m->lock);
    *pacquired = (status == APR_SUCCESS);
    if (*pacquired) {
        apr_threadkey_private_set(m->lock, thread_lock);
    }
    return status;
}

static void leave_mutex(h2_mplx *m, int acquired)
{
    if (acquired) {
        apr_threadkey_private_set(NULL, thread_lock);
        apr_thread_mutex_unlock(m->lock);
    }
}

static int is_aborted(h2_mplx *m, apr_status_t *pstatus)
{
    AP_DEBUG_ASSERT(m);
    if (m->aborted) {
        *pstatus = APR_ECONNABORTED;
        return 1;
    }
    return 0;
}

static void have_out_data_for(h2_mplx *m, int stream_id);

static void check_tx_reservation(h2_mplx *m) 
{
    if (m->tx_handles_reserved == 0) {
        m->tx_handles_reserved += h2_workers_tx_reserve(m->workers, 
            H2MIN(m->tx_chunk_size, h2_io_set_size(m->stream_ios)));
    }
}

static void check_tx_free(h2_mplx *m) 
{
    if (m->tx_handles_reserved > m->tx_chunk_size) {
        apr_size_t count = m->tx_handles_reserved - m->tx_chunk_size;
        m->tx_handles_reserved = m->tx_chunk_size;
        h2_workers_tx_free(m->workers, count);
    }
    else if (m->tx_handles_reserved 
             && (!m->stream_ios || h2_io_set_is_empty(m->stream_ios))) {
        h2_workers_tx_free(m->workers, m->tx_handles_reserved);
        m->tx_handles_reserved = 0;
    }
}

static void h2_mplx_destroy(h2_mplx *m)
{
    AP_DEBUG_ASSERT(m);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  "h2_mplx(%ld): destroy, ios=%d", 
                  m->id, (int)h2_io_set_size(m->stream_ios));
    check_tx_free(m);
    if (m->pool) {
        apr_pool_destroy(m->pool);
    }
}

/**
