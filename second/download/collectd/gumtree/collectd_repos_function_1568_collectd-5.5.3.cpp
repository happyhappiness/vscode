static int ceph_init(void)
{
    int ret;
    ceph_daemons_print();

    ret = cconn_main_loop(ASOK_REQ_VERSION);

    return (ret) ? ret : 0;
}