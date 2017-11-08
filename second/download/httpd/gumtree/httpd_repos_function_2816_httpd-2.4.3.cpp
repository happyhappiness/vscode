void ap_down_server_cb(void *a, void *b)
{
    nlmUnloadSignaled(0);
    return;
}