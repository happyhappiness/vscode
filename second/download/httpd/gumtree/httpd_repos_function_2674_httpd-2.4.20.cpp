void h2_stream_set_add(h2_stream_set *sp, h2_stream *stream)
{
    apr_hash_set(sp->hash, &stream->id, sizeof(stream->id), stream);
}