int h2_stream_set_has_unsubmitted(h2_stream_set *sp)
{
    int has_unsubmitted = 0;
    h2_stream_set_iter(sp, unsubmitted_iter, &has_unsubmitted);
    return has_unsubmitted;
}