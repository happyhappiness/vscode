static int rst_unprocessed_stream(h2_stream *stream, void *ctx)
{
    int unprocessed = (!h2_stream_was_closed(stream)
                       && (H2_STREAM_CLIENT_INITIATED(stream->id)? 
                           (!stream->session->local.accepting
                            && stream->id > stream->session->local.accepted_max)
                            : 
                           (!stream->session->remote.accepting
                            && stream->id > stream->session->remote.accepted_max))
                       ); 
    if (unprocessed) {
        h2_stream_rst(stream, H2_ERR_NO_ERROR);
        return 0;
    }
    return 1;
}