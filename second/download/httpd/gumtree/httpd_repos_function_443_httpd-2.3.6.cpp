static ap_log_writer_init* ap_log_set_writer_init(ap_log_writer_init *handle)
{
    ap_log_writer_init *old = log_writer_init;
    log_writer_init = handle;

    return old;

}