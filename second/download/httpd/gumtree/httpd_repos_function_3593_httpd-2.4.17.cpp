static apr_status_t cfg_close(void *param)
{
    return apr_file_close(param);
}