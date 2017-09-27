            break;
        }
    } while (!async_mpm
             && c->keepalive == AP_CONN_KEEPALIVE 
             && mpm_state != AP_MPMQ_STOPPING);
    
    return DONE;
}

apr_status_t h2_conn_pre_close(struct h2_ctx *ctx, conn_rec *c)
{
    apr_status_t status;
    
    status = h2_session_pre_close(h2_ctx_session_get(ctx), async_mpm);
    if (status == APR_SUCCESS) {
        return DONE; /* This is the same, right? */
    }
    return status;
}

conn_rec *h2_slave_create(conn_rec *master, int slave_id, apr_pool_t *parent)
{
    apr_allocator_t *allocator;
    apr_pool_t *pool;
    conn_rec *c;
    void *cfg;
    
    ap_assert(master);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, master,
                  "h2_conn(%ld): create slave", master->id);
    
    /* We create a pool with its own allocator to be used for
     * processing a request. This is the only way to have the processing
     * independant of its parent pool in the sense that it can work in
     * another thread.
     */
    apr_allocator_create(&allocator);
    apr_pool_create_ex(&pool, parent, NULL, allocator);
    apr_pool_tag(pool, "h2_slave_conn");
    apr_allocator_owner_set(allocator, pool);

    c = (conn_rec *) apr_palloc(pool, sizeof(conn_rec));
    if (c == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, master, 
                      APLOGNO(02913) "h2_task: creating conn");
        return NULL;
    }
    
    memcpy(c, master, sizeof(conn_rec));
        
    c->master                 = master;
