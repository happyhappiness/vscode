static apr_status_t setptr(apr_file_t *thefile, unsigned long pos )
{
    long newbufpos;
    ULONG rc;

    if (thefile->direction == 1) {
        /* XXX: flush here is not mutex protected */
        apr_status_t rv = apr_file_flush(thefile);

        if (rv != APR_SUCCESS) {
            return rv;
        }

        thefile->bufpos = thefile->direction = thefile->dataRead = 0;
    }

    newbufpos = pos - (thefile->filePtr - thefile->dataRead);
    if (newbufpos >= 0 && newbufpos <= thefile->dataRead) {
        thefile->bufpos = newbufpos;
        rc = 0;
    } else {
        rc = DosSetFilePtr(thefile->filedes, pos, FILE_BEGIN, &thefile->filePtr );

        if ( !rc )
            thefile->bufpos = thefile->dataRead = 0;
    }

    return APR_FROM_OS_ERROR(rc);
}