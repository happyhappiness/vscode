static char *native_strerror(apr_status_t statcode, char *buf,
                             apr_size_t bufsize)
{
#ifdef _WIN32_WCE
    static char err[32];
    sprintf(err, "Native Error #%d", statcode);
    return stuffbuffer(buf, bufsize, err);
#else
    return stuffbuffer(buf, bufsize, strerror(statcode));
#endif
}