            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                          APLOGNO(02929) "nghttp2_session_server_new: %s",
                          nghttp2_strerror(rv));
            h2_session_destroy(session);
            return NULL;
        }
         
        n = h2_config_geti(session->config, H2_CONF_PUSH_DIARY_SIZE);
        session->push_diary = h2_push_diary_create(session->pool, n);
        
        if (APLOGcdebug(c)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03200)
                          "h2_session(%ld) created, max_streams=%d, "
                          "stream_mem=%d, workers_limit=%d, workers_max=%d, "
                          "push_diary(type=%d,N=%d)",
                          session->id, (int)session->max_stream_count, 
                          (int)session->max_stream_mem,
                          session->mplx->workers_limit, 
                          session->mplx->workers_max, 
                          session->push_diary->dtype, 
                          (int)session->push_diary->N);
        }
    }
    return session;
}

h2_session *h2_session_create(conn_rec *c, h2_ctx *ctx, h2_workers *workers)
{
    return h2_session_create_int(c, NULL, ctx, workers);
}

h2_session *h2_session_rcreate(request_rec *r, h2_ctx *ctx, h2_workers *workers)
{
    return h2_session_create_int(r->connection, r, ctx, workers);
}

void h2_session_eoc_callback(h2_session *session)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "session(%ld): cleanup and destroy", session->id);
    apr_pool_cleanup_kill(session->pool, session, session_pool_cleanup);
    h2_session_destroy(session);
