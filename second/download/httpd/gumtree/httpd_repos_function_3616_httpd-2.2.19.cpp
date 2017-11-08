apr_status_t apr_file_trunc(apr_file_t *fp, apr_off_t offset)
{
    if (ftruncate(fp->filedes, offset) == -1) {
        return errno;
    }
    return apr_file_seek(fp, APR_SET, &offset);
}