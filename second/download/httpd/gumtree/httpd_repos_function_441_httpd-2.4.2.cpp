static const char *set_buffered_logs_on(cmd_parms *parms, void *dummy, int flag)
{
    buffered_logs = flag;
    if (buffered_logs) {
        ap_log_set_writer_init(ap_buffered_log_writer_init);
        ap_log_set_writer(ap_buffered_log_writer);
    }
    else {
        ap_log_set_writer_init(ap_default_log_writer_init);
        ap_log_set_writer(ap_default_log_writer);
    }
    return NULL;
}