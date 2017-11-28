int
clientHttpRequestStatus(int fd, ClientHttpRequest const *http)
{
#if SIZEOF_INT64_T == 4
    if (http->out.size > 0x7FFF0000) {
        debugs(88, DBG_IMPORTANT, "WARNING: closing FD " << fd << " to prevent out.size counter overflow");
        if (http->getConn())
            debugs(88, DBG_IMPORTANT, "\tclient " << http->getConn()->peer);
        debugs(88, DBG_IMPORTANT, "\treceived " << http->out.size << " bytes");
        debugs(88, DBG_IMPORTANT, "\tURI " << http->log_uri);
        return 1;
    }

    if (http->out.offset > 0x7FFF0000) {
        debugs(88, DBG_IMPORTANT, "WARNING: closing FD " << fd < " to prevent out.offset counter overflow");
        if (http->getConn())
            debugs(88, DBG_IMPORTANT, "\tclient " << http->getConn()->peer);
        debugs(88, DBG_IMPORTANT, "\treceived " << http->out.size << " bytes, offset " << http->out.offset);
        debugs(88, DBG_IMPORTANT, "\tURI " << http->log_uri);
        return 1;
    }

#endif
    return 0;
}