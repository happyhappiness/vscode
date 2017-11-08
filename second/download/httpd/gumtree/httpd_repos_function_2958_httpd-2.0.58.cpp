static apr_status_t setptr(apr_file_t *thefile, apr_off_t pos )
{
    apr_off_t newbufpos;
    apr_status_t rv;
    DWORD rc;

    if (thefile->direction == 1) {
        /* XXX: flush here is not mutex protected */
        rv = apr_file_flush(thefile);
        if (rv != APR_SUCCESS)
            return rv;
        thefile->bufpos = thefile->direction = thefile->dataRead = 0;
    }

    newbufpos = pos - (thefile->filePtr - thefile->dataRead);

    if (newbufpos >= 0 && newbufpos <= thefile->dataRead) {
        thefile->bufpos = (apr_size_t)newbufpos;
        rv = APR_SUCCESS;
    } else {
        DWORD offlo = (DWORD)pos;
        DWORD offhi = (DWORD)(pos >> 32);
        rc = SetFilePointer(thefile->filehand, offlo, &offhi, FILE_BEGIN);

        if (rc == (DWORD)-1)
            /* A legal value, perhaps?  MSDN implies prior SetLastError isn't
             * needed, googling for SetLastError SetFilePointer seems
             * to confirm this.  INVALID_SET_FILE_POINTER is too recently
             * added for us to rely on it as a constant.
             */
            rv = apr_get_os_error();
        else
            rv = APR_SUCCESS;

        if (rv == APR_SUCCESS) {
            thefile->eof_hit = thefile->bufpos = thefile->dataRead = 0;
            thefile->filePtr = pos;
        }
    }

    return rv;
}