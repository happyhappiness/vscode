static apr_status_t ef_close_file(void *vfile)
{
    return apr_file_close(vfile);
}