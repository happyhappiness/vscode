static SSL_SESSION *
get_session_cb(SSL *, unsigned char *sessionID, int len, int *copy)
{
    if (!SslSessionCache)
        return NULL;

    SSL_SESSION *session = NULL;
    const unsigned int *p;
    p = (unsigned int *)sessionID;
    debugs(83, 5, "Request to search for SSL Session of len:" <<
           len << p[0] << ":" << p[1]);

    int pos;
    Ipc::MemMap::Slot const *slot = SslSessionCache->openForReading((const cache_key*)sessionID, pos);
    if (slot != NULL) {
        if (slot->expire > squid_curtime) {
            const unsigned char *ptr = slot->p;
            session = d2i_SSL_SESSION(NULL, &ptr, slot->pSize);
            debugs(83, 5, "Session retrieved from cache at pos " << pos);
        } else
            debugs(83, 5, "Session in cache expired");
        SslSessionCache->closeForReading(pos);
    }

    if (!session)
        debugs(83, 5, "Failed to retrieved from cache\n");

    // With the parameter copy the callback can require the SSL engine
    // to increment the reference count of the SSL_SESSION object, Normally
    // the reference count is not incremented and therefore the session must
    // not be explicitly freed with SSL_SESSION_free(3).
    *copy = 0;
    return session;
}