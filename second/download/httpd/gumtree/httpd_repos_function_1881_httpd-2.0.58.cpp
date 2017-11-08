static apr_status_t piped_log_cleanup(void *data)
{
    piped_log *pl = data;

    apr_file_close(ap_piped_log_write_fd(pl));
    return APR_SUCCESS;
}