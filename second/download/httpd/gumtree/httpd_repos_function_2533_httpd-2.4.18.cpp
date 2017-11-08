int h2_stream_set_is_empty(h2_stream_set *sp)
{
    return apr_hash_count(sp->hash) == 0;
}