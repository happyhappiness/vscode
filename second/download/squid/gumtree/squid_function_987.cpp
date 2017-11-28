bool
ConnStateData::proxyProtocolError(const char *msg)
{
    if (msg) {
        // This is important to know, but maybe not so much that flooding the log is okay.
#if QUIET_PROXY_PROTOCOL
        // display the first of every 32 occurances at level 1, the others at level 2.
        static uint8_t hide = 0;
        debugs(33, (hide++ % 32 == 0 ? DBG_IMPORTANT : 2), msg << " from " << clientConnection);
#else
        debugs(33, DBG_IMPORTANT, msg << " from " << clientConnection);
#endif
        mustStop(msg);
    }
    return false;
}