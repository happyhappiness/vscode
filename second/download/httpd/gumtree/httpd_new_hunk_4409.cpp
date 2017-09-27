                          APLOGNO(02938) "h2_stream(%ld-%d): reading data",
                          session->id, (int)stream_id);
            return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (eos) {
        *data_flags |= NGHTTP2_DATA_FLAG_EOF;
    }
    return (ssize_t)nread;
}

struct h2_stream *h2_session_push(h2_session *session, h2_stream *is,
                                  h2_push *push)
{
    apr_status_t status;
    h2_stream *stream;
    h2_ngheader *ngh;
