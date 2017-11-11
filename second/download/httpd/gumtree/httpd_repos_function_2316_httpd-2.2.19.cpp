apr_status_t ap_fatal_signal_child_setup(server_rec *s)
{
    my_pid = getpid();
    return APR_SUCCESS;
}