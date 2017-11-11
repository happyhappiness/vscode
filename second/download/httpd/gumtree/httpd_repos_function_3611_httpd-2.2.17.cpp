static apr_status_t file_read_buffered(apr_file_t *thefile, void *buf,
                                       apr_size_t *nbytes)
{
    apr_ssize_t rv;
    char *pos = (char *)buf;
    apr_uint64_t blocksize;
    apr_uint64_t size = *nbytes;

    if (thefile->direction == 1) {
        rv = apr_file_flush_locked(thefile);
        if (rv) {
            return rv;
        }
        thefile->bufpos = 0;
        thefile->direction = 0;
        thefile->dataRead = 0;
    }

    rv = 0;
    if (thefile->ungetchar != -1) {
        *pos = (char)thefile->ungetchar;
        ++pos;
        --size;
        thefile->ungetchar = -1;
    }
    while (rv == 0 && size > 0) {
        if (thefile->bufpos >= thefile->dataRead) {
            int bytesread = read(thefile->filedes, thefile->buffer, 
                                 thefile->bufsize);
            if (bytesread == 0) {
                thefile->eof_hit = TRUE;
                rv = APR_EOF;
                break;
            }
            else if (bytesread == -1) {
                rv = errno;
                break;
            }
            thefile->dataRead = bytesread;
            thefile->filePtr += thefile->dataRead;
            thefile->bufpos = 0;
        }

        blocksize = size > thefile->dataRead - thefile->bufpos ? thefile->dataRead - thefile->bufpos : size;
        memcpy(pos, thefile->buffer + thefile->bufpos, blocksize);
        thefile->bufpos += blocksize;
        pos += blocksize;
        size -= blocksize;
    }

    *nbytes = pos - (char *)buf;
    if (*nbytes) {
        rv = 0;
    }
    return rv;
}