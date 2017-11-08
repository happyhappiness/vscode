int h2_stream_is_suspended(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    return stream->suspended;
}