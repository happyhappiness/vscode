void h2_stream_set_remove(h2_stream_set *sp, int stream_id)
{
    apr_hash_set(sp->hash, &stream_id, sizeof(stream_id), NULL);
}