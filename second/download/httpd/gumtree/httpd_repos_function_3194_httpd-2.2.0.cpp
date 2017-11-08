static apr_status_t setptr(apr_file_t *thefile, apr_off_t pos )
{
    apr_off_t newbufpos;
    int rc;

    if (thefile->direction == 1) {
        apr_file_flush(thefile);
        thefile->bufpos = thefile->direction = thefile->dataRead = 0;
    }

    newbufpos = pos - (thefile->filePtr - thefile->dataRead);
    if (newbufpos >= 0 && newbufpos <= thefile->dataRead) {
        thefile->bufpos = newbufpos;
        rc = 0;
    } 
    else {
        rc = lseek(thefile->filedes, pos, SEEK_SET);

        if (rc != -1 ) {
            thefile->bufpos = thefile->dataRead = 0;
            thefile->filePtr = pos;
            rc = 0;
        }
        else {
            rc = errno;
        }
    }

    return rc;
}