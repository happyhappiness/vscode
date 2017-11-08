apr_status_t apr_file_trunc(apr_file_t *fp, apr_off_t offset)
{
    if (fp->buffered) {
        int rc = 0;
        file_lock(fp);
        if (fp->direction == 1 && fp->bufpos != 0) {
            apr_off_t len = fp->filePtr + fp->bufpos;
            if (offset < len) {
                /* New file end fall below our write buffer limit.
                 * Figure out if and what needs to be flushed.
                 */
                apr_off_t off = len - offset;
                if (off >= 0 && off <= fp->bufpos)
                    fp->bufpos = fp->bufpos - (size_t)off;
                else
                    fp->bufpos = 0;
            }
            rc = apr_file_flush_locked(fp);
            /* Reset buffer positions for write mode */
            fp->bufpos = fp->direction = fp->dataRead = 0;
        }
        file_unlock(fp);
        if (rc) {
            return rc;
        }
    }
    if (ftruncate(fp->filedes, offset) == -1) {
        return errno;
    }
    return apr_file_seek(fp, APR_SET, &offset);
}