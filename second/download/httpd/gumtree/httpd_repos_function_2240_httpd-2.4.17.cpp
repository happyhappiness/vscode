void h2_stream_abort(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    stream->aborted = 1;
}