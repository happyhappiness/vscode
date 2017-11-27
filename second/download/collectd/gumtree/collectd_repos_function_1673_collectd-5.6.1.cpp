static int ceph_read(void)
{
    return cconn_main_loop(ASOK_REQ_DATA);
}