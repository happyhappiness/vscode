static int
store_session_cb(SSL *ssl, SSL_SESSION *session)
{
    if (!SessionCache)
        return 0;

    debugs(83, 5, "Request to store SSL_SESSION");

    SSL_SESSION_set_timeout(session, Config.SSL.session_ttl);

#if HAVE_LIBSSL_SSL_SESSION_GET_ID
    unsigned int idlen;
    const unsigned char *id = SSL_SESSION_get_id(session, &idlen);
#else
    unsigned char *id = session->session_id;
    unsigned int idlen = session->session_id_length;
#endif
    // XXX: the other calls [to openForReading()] do not copy the sessionId to a char buffer, does this really have to?
    unsigned char key[MEMMAP_SLOT_KEY_SIZE];
    // Session ids are of size 32bytes. They should always fit to a
    // MemMap::Slot::key
    assert(idlen <= MEMMAP_SLOT_KEY_SIZE);
    memset(key, 0, sizeof(key));
    memcpy(key, id, idlen);
    int pos;
    if (auto slotW = SessionCache->openForWriting(static_cast<const cache_key*>(key), pos)) {
        int lenRequired = i2d_SSL_SESSION(session, nullptr);
        if (lenRequired <  MEMMAP_SLOT_DATA_SIZE) {
            unsigned char *p = static_cast<unsigned char *>(slotW->p);
            lenRequired = i2d_SSL_SESSION(session, &p);
            slotW->set(key, nullptr, lenRequired, squid_curtime + Config.SSL.session_ttl);
        }
        SessionCache->closeForWriting(pos);
        debugs(83, 5, "wrote an SSL_SESSION entry of size " << lenRequired << " at pos " << pos);
    }
    return 0;
}