static apr_size_t trim_busy_threads(apr_thread_pool_t *me, apr_size_t cnt)
{
    trim_threads(me, &cnt, 0);
    return cnt;
}