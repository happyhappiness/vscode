#include "h2_workers.h"

static int frame_print(const nghttp2_frame *frame, char *buffer, size_t maxlen);

static int h2_session_status_from_apr_status(apr_status_t rv)
{
    switch (rv) {
        case APR_SUCCESS:
            return NGHTTP2_NO_ERROR;
        case APR_EAGAIN:
        case APR_TIMEUP:
            return NGHTTP2_ERR_WOULDBLOCK;
        case APR_EOF:
            return NGHTTP2_ERR_EOF;
        default:
            return NGHTTP2_ERR_PROTO;
    }
}

static int stream_open(h2_session *session, int stream_id)
{
    h2_stream * stream;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    stream = h2_mplx_open_io(session->mplx, stream_id);
    if (stream) {
        h2_stream_set_add(session->streams, stream);
        if (stream->id > session->max_stream_received) {
            session->max_stream_received = stream->id;
        }
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session: stream(%ld-%d): opened",
                      session->id, stream_id);
        
        return 0;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, session->c,
                  APLOGNO(02918) 
                  "h2_session: stream(%ld-%d): unable to create",
                  session->id, stream_id);
    return NGHTTP2_ERR_INVALID_STREAM_ID;
}

static apr_status_t stream_end_headers(h2_session *session,
                                       h2_stream *stream, int eos)
{
    (void)session;
    return h2_stream_write_eoh(stream, eos);
}

static apr_status_t send_data(h2_session *session, const char *data, 
                              apr_size_t length);

/*
 * Callback when nghttp2 wants to send bytes back to the client.
 */
static ssize_t send_cb(nghttp2_session *ngh2,
                       const uint8_t *data, size_t length,
                       int flags, void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = send_data(session, (const char *)data, length);
    
    (void)ngh2;
    (void)flags;
    if (status == APR_SUCCESS) {
        return length;
    }
    if (status == APR_EAGAIN || status == APR_TIMEUP) {
        return NGHTTP2_ERR_WOULDBLOCK;
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session: send error");
    return h2_session_status_from_apr_status(status);
}
