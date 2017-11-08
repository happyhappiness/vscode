static char *native_strerror(apr_status_t statcode, char *buf,
                             apr_size_t bufsize)
{
    if (strerror_r(statcode, buf, bufsize) < 0) {
        return stuffbuffer(buf, bufsize, 
                           "APR does not understand this error code");
    }
    else {
        return buf;
    }
}