apr_status_t apr_dir_close(apr_dir_t *thedir)
{
    return apr_pool_cleanup_run(thedir->pool, thedir, dir_cleanup);
}