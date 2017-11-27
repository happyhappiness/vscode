static int ceph_shutdown(void)
{
    int i;
    for(i = 0; i < g_num_daemons; ++i)
    {
        ceph_daemon_free(g_daemons[i]);
    }
    sfree(g_daemons);
    g_daemons = NULL;
    g_num_daemons = 0;
    DEBUG("ceph plugin: finished ceph_shutdown");
    return 0;
}