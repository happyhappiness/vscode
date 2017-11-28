void
Ssl::initialize_session_cache()
{

    if (!isSslServer()) //no need to configure ssl session cache.
        return;

    // Check if the MemMap keys and data are enough big to hold
    // session ids and session data
    assert(SSL_SESSION_ID_SIZE >= MEMMAP_SLOT_KEY_SIZE);
    assert(SSL_SESSION_MAX_SIZE >= MEMMAP_SLOT_DATA_SIZE);

    int configuredItems = ::Config.SSL.sessionCacheSize / sizeof(Ipc::MemMap::Slot);
    if (IamWorkerProcess() && configuredItems)
        SslSessionCache = new Ipc::MemMap(SslSessionCacheName);
    else {
        SslSessionCache = NULL;
        return;
    }

    for (AnyP::PortCfgPointer s = HttpsPortList; s != NULL; s = s->next) {
        if (s->staticSslContext.get() != NULL)
            setSessionCallbacks(s->staticSslContext.get());
    }

    for (AnyP::PortCfgPointer s = HttpPortList; s != NULL; s = s->next) {
        if (s->staticSslContext.get() != NULL)
            setSessionCallbacks(s->staticSslContext.get());
    }
}