static int
store_session_cb(SSL *ssl, SSL_SESSION *session)
{
    if (!SslSessionCache)
        return 0;

    debugs(83, 5, "Request to store SSL Session ");

    SSL_SESSION_set_timeout(session, Config.SSL.session_ttl);

    unsigned char *id = session->session_id;
    unsigned int idlen = session->session_id_length;
    unsigned char key[MEMMAP_SLOT_KEY_SIZE];
    // Session ids are of size 32bytes. They should always fit to a
    // MemMap::Slot::key
    assert(idlen <= MEMMAP_SLOT_KEY_SIZE);
    memset(key, 0, sizeof(key));
    memcpy(key, id, idlen);
    int pos;
    Ipc::MemMap::Slot *slotW = SslSessionCache->openForWriting((const cache_key*)key, pos);
    if (slotW) {
        int lenRequired =  i2d_SSL_SESSION(session, NULL);
        if (lenRequired <  MEMMAP_SLOT_DATA_SIZE) {
            unsigned char *p = (unsigned char *)slotW->p;
            lenRequired = i2d_SSL_SESSION(session, &p);
            slotW->set(key, NULL, lenRequired, squid_curtime + Config.SSL.session_ttl);
        }
        SslSessionCache->closeForWriting(pos);
        debugs(83, 5, "wrote an ssl session entry of size " << lenRequired << " at pos " << pos);
    }
    return 0;
}