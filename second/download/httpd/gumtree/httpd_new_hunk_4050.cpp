            return 1;
        default:
            return 0;
    }
}

static h2_sos *h2_sos_mplx_create(h2_stream *stream, h2_response *response);

h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session)
{
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    stream->id        = id;
    stream->state     = H2_STREAM_ST_IDLE;
    stream->pool      = pool;
    stream->session   = session;
    set_state(stream, H2_STREAM_ST_OPEN);
    stream->request   = h2_request_create(id, pool, 
        h2_config_geti(session->config, H2_CONF_SER_HEADERS));
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
                  "h2_stream(%ld-%d): opened", session->id, stream->id);
    return stream;
}

apr_status_t h2_stream_destroy(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
    }
    return APR_SUCCESS;
}

