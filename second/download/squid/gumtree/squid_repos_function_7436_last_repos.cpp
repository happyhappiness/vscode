void
SharedSessionCacheRr::create()
{
    if (!isTlsServer()) // no need to configure SSL_SESSION* cache.
        return;

#if USE_OPENSSL
    if (int items = Config.SSL.sessionCacheSize / sizeof(Ipc::MemMap::Slot))
        owner = Ipc::MemMap::Init(SessionCacheName, items);
#endif
}