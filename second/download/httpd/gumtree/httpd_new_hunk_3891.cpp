#include "h2_workers.h"

static int frame_print(const nghttp2_frame *frame, char *buffer, size_t maxlen);

static int h2_session_status_from_apr_status(apr_status_t rv)
{
    if (rv == APR_SUCCESS) {
        return NGHTTP2_NO_ERROR;
    }
    else if (APR_STATUS_IS_EAGAIN(rv)) {
        return NGHTTP2_ERR_WOULDBLOCK;
    }
    else if (APR_STATUS_IS_EOF(rv)) {
            return NGHTTP2_ERR_EOF;
    }
    return NGHTTP2_ERR_PROTO;
}

static void update_window(void *ctx, int stream_id, apr_off_t bytes_read)
{
    h2_session *session = (h2_session*)ctx;
    nghttp2_session_consume(session->ngh2, stream_id, bytes_read);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                  "h2_session(%ld-%d): consumed %ld bytes",
                  session->id, stream_id, (long)bytes_read);
}


h2_stream *h2_session_open_stream(h2_session *session, int stream_id)
{
    h2_stream * stream;
    apr_pool_t *stream_pool;
    if (session->aborted) {
        return NULL;
    }
    
    if (session->spare) {
        stream_pool = session->spare;
        session->spare = NULL;
    }
    else {
        apr_pool_create(&stream_pool, session->pool);
    }
    
    stream = h2_stream_open(stream_id, stream_pool, session);
    
    h2_stream_set_add(session->streams, stream);
    if (H2_STREAM_CLIENT_INITIATED(stream_id)
        && stream_id > session->max_stream_received) {
        session->max_stream_received = stream->id;
    }
    
    return stream;
}

#ifdef H2_NG2_STREAM_API

/**
 * Determine the importance of streams when scheduling tasks.
 * - if both stream depend on the same one, compare weights
 * - if one stream is closer to the root, prioritize that one
 * - if both are on the same level, use the weight of their root
 *   level ancestors
 */
static int spri_cmp(int sid1, nghttp2_stream *s1, 
                    int sid2, nghttp2_stream *s2, h2_session *session)
{
    nghttp2_stream *p1, *p2;
    
    p1 = nghttp2_stream_get_parent(s1);
    p2 = nghttp2_stream_get_parent(s2);
    
    if (p1 == p2) {
        int32_t w1, w2;
        
        w1 = nghttp2_stream_get_weight(s1);
        w2 = nghttp2_stream_get_weight(s2);
        return w2 - w1;
    }
    else if (!p1) {
        /* stream 1 closer to root */
        return -1;
    }
    else if (!p2) {
        /* stream 2 closer to root */
        return 1;
    }
    return spri_cmp(sid1, p1, sid2, p2, session);
}

static int stream_pri_cmp(int sid1, int sid2, void *ctx)
{
    h2_session *session = ctx;
    nghttp2_stream *s1, *s2;
    
    s1 = nghttp2_session_find_stream(session->ngh2, sid1);
    s2 = nghttp2_session_find_stream(session->ngh2, sid2);

    if (s1 == s2) {
        return 0;
    }
    else if (!s1) {
        return 1;
    }
    else if (!s2) {
        return -1;
    }
    return spri_cmp(sid1, s1, sid2, s2, session);
}

#else /* ifdef H2_NG2_STREAM_API */

/* In absence of nghttp2_stream API, which gives information about
 * priorities since nghttp2 1.3.x, we just sort the streams by
 * their identifier, aka. order of arrival.
 */
static int stream_pri_cmp(int sid1, int sid2, void *ctx)
{
    (void)ctx;
    return sid1 - sid2;
}

#endif /* (ifdef else) H2_NG2_STREAM_API */

static apr_status_t stream_schedule(h2_session *session,
                                    h2_stream *stream, int eos)
{
    (void)session;
    return h2_stream_schedule(stream, eos, stream_pri_cmp, session);
}

/*
 * Callback when nghttp2 wants to send bytes back to the client.
 */
static ssize_t send_cb(nghttp2_session *ngh2,
                       const uint8_t *data, size_t length,
                       int flags, void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status;
    
    (void)ngh2;
    (void)flags;
    status = h2_conn_io_write(&session->io, (const char *)data, length);
    if (status == APR_SUCCESS) {
        return length;
    }
    if (APR_STATUS_IS_EAGAIN(status)) {
        return NGHTTP2_ERR_WOULDBLOCK;
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session: send error");
    return h2_session_status_from_apr_status(status);
}
