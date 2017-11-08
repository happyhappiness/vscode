h2_stream *h2_stream_set_get(h2_stream_set *sp, int stream_id)
{
    return apr_hash_get(sp->hash, &stream_id, sizeof(stream_id));
}