static char *native_strerror(apr_status_t statcode, char *buf,
                             apr_size_t bufsize)
{
    const char *msg;

    buf[0] = '\0';
    msg = strerror_r(statcode, buf, bufsize);
    if (buf[0] == '\0') { /* libc didn't use our buffer */
        return stuffbuffer(buf, bufsize, msg);
    }
    else {
        return buf;
    }
}