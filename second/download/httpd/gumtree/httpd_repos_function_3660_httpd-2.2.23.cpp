static apr_status_t setptr(apr_file_t *thefile, apr_off_t pos )
{
    apr_off_t newbufpos;
    apr_status_t rv;

    if (thefile->direction == 1) {
        rv = apr_file_flush_locked(thefile);
        if (rv) {
            return rv;
        }
        thefile->bufpos = thefile->direction = thefile->dataRead = 0;
    }

    newbufpos = pos - (thefile->filePtr - thefile->dataRead);
    if (newbufpos >= 0 && newbufpos <= thefile->dataRead) {
        thefile->bufpos = newbufpos;
        rv = APR_SUCCESS;
    }
    else {
        if (lseek(thefile->filedes, pos, SEEK_SET) != -1) {
            thefile->bufpos = thefile->dataRead = 0;
            thefile->filePtr = pos;
            rv = APR_SUCCESS;
        }
        else {
            rv = errno;
        }
    }

    return rv;
}