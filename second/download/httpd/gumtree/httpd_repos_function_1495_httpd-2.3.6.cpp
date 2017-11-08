static void status_child_init(apr_pool_t *p, server_rec *s)
{
    child_pid = getpid();
}