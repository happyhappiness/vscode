static ap_log_writer *ap_log_set_writer(ap_log_writer *handle)
{
    ap_log_writer *old = log_writer;
    log_writer = handle;

    return old;
}