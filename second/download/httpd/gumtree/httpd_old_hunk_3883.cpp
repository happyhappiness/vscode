
static void have_out_data_for(h2_mplx *m, int stream_id);

static void h2_mplx_destroy(h2_mplx *m)
{
    AP_DEBUG_ASSERT(m);
    m->aborted = 1;
    if (m->q) {
        h2_tq_destroy(m->q);
        m->q = NULL;
    }
    if (m->ready_ios) {
        h2_io_set_destroy(m->ready_ios);
        m->ready_ios = NULL;
    }
    if (m->stream_ios) {
        h2_io_set_destroy(m->stream_ios);
        m->stream_ios = NULL;
    }
    
    if (m->lock) {
        apr_thread_mutex_destroy(m->lock);
        m->lock = NULL;
    }
    
    if (m->pool) {
        apr_pool_destroy(m->pool);
    }
}

/**
