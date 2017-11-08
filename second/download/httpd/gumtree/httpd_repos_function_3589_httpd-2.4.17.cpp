static apr_status_t piped_log_cleanup(void *data)
{
    piped_log *pl = data;

    apr_file_close(pl->write_fd);
    return APR_SUCCESS;
}