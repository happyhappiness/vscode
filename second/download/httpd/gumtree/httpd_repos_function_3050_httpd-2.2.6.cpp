static char *native_strerror(apr_status_t statcode, char *buf,
                             apr_size_t bufsize)
{
#ifdef _WIN32_WCE
    static char err[32];
    sprintf(err, "Native Error #%d", statcode);
    return stuffbuffer(buf, bufsize, err);
#else
    const char *err = strerror(statcode);
    if (err) {
        return stuffbuffer(buf, bufsize, err);
    } else {
        return stuffbuffer(buf, bufsize, 
                           "APR does not understand this error code");
    }
#endif
}