static apr_status_t dir_cleanup(void *thedir)
{
    apr_dir_t *dir = thedir;
    return apr_dir_close(dir);
}