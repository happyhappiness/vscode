            break;
        }
    } while (!async_mpm
             && c->keepalive == AP_CONN_KEEPALIVE 
             && mpm_state != AP_MPMQ_STOPPING);
    
    if (c->cs) {
        switch (session->state) {
            case H2_SESSION_ST_INIT:
            case H2_SESSION_ST_CLEANUP:
            case H2_SESSION_ST_DONE:
            case H2_SESSION_ST_IDLE:
                c->cs->state = CONN_STATE_WRITE_COMPLETION;
                break;
            case H2_SESSION_ST_BUSY:
            case H2_SESSION_ST_WAIT:
            default:
                c->cs->state = CONN_STATE_HANDLER;
                break;
                
        }
    }
    
    return DONE;
}

apr_status_t h2_conn_pre_close(struct h2_ctx *ctx, conn_rec *c)
{
    h2_session *session = h2_ctx_session_get(ctx);
    if (session) {
        apr_status_t status = h2_session_pre_close(session, async_mpm);
        return (status == APR_SUCCESS)? DONE : status;
    }
    return DONE;
}

conn_rec *h2_slave_create(conn_rec *master, int slave_id, apr_pool_t *parent)
{
    apr_allocator_t *allocator;
    apr_status_t status;
    apr_pool_t *pool;
    conn_rec *c;
    void *cfg;
    module *mpm;
    
    ap_assert(master);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, master,
                  "h2_stream(%ld-%d): create slave", master->id, slave_id);
    
    /* We create a pool with its own allocator to be used for
     * processing a request. This is the only way to have the processing
     * independant of its parent pool in the sense that it can work in
     * another thread. Also, the new allocator needs its own mutex to
     * synchronize sub-pools.
     */
    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    status = apr_pool_create_ex(&pool, parent, NULL, allocator);
    if (status != APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, master, 
                      APLOGNO(10004) "h2_session(%ld-%d): create slave pool",
                      master->id, slave_id);
        return NULL;
    }
    apr_allocator_owner_set(allocator, pool);
    apr_pool_tag(pool, "h2_slave_conn");
 
    c = (conn_rec *) apr_palloc(pool, sizeof(conn_rec));
    if (c == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, master, 
                      APLOGNO(02913) "h2_session(%ld-%d): create slave",
                      master->id, slave_id);
        apr_pool_destroy(pool);
        return NULL;
    }
    
    memcpy(c, master, sizeof(conn_rec));
        
    c->master                 = master;
