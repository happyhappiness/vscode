static int ceph_shutdown(void)
{
    for(size_t i = 0; i < g_num_daemons; ++i)
    {
        ceph_daemon_free(g_daemons[i]);
    }
    sfree(g_daemons);
    g_daemons = NULL;
    g_num_daemons = 0;
    DEBUG("ceph plugin: finished ceph_shutdown");
    return 0;
}