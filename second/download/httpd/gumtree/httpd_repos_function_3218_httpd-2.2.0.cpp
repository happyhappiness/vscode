static apr_status_t setptr(apr_file_t *thefile, apr_off_t pos )
{
    apr_size_t newbufpos;
    DWORD rc;

    if (thefile->direction == 1) {
        apr_file_flush(thefile);
        thefile->bufpos = thefile->dataRead = 0;
        thefile->direction = 0;
    }

    /* We may be truncating to size here. 
     * XXX: testing an 'unsigned' as >= 0 below indicates a bug
     */
    newbufpos = (apr_size_t)(pos - (thefile->filePtr 
                                  - thefile->dataRead));

    if (newbufpos >= 0 && newbufpos <= thefile->dataRead) {
        thefile->bufpos = (apr_size_t)newbufpos;
        rc = 0;
    } else {
        DWORD offlo = (DWORD)pos;
        DWORD offhi = (DWORD)(pos >> 32);
        rc = SetFilePointer(thefile->filehand, offlo, &offhi, FILE_BEGIN);

        if (rc == 0xFFFFFFFF)
            rc = apr_get_os_error();
        else
            rc = APR_SUCCESS;
        if (rc == APR_SUCCESS) {
            thefile->eof_hit = 0;
            thefile->bufpos = thefile->dataRead = 0;
            thefile->filePtr = pos;
        }
    }

    return rc;
}