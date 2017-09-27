        h2_stream_set_iter(session->streams, resume_on_data, &ctx);
        return ctx.resume_count;
    }
    return 0;
}

h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
{
    if (!session->last_stream || stream_id != session->last_stream->id) {
        session->last_stream = h2_stream_set_get(session->streams, stream_id);
    }
    return session->last_stream;
}

/* h2_io_on_read_cb implementation that offers the data read
 * directly to the session for consumption.
 */
static apr_status_t session_receive(const char *data, apr_size_t len,
