int h2_stream_set_has_suspended(h2_stream_set *sp)
{
    int has_suspended = 0;
    h2_stream_set_iter(sp, suspended_iter, &has_suspended);
    return has_suspended;
}