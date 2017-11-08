apr_status_t apr_unix_child_file_cleanup(void *thefile)
{
    return file_cleanup(thefile);
}