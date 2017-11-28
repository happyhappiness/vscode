void
SharedSessionCacheRr::useConfig()
{
#if USE_OPENSSL
    if (SessionCache || !isTlsServer()) // no need to configure SSL_SESSION* cache.
        return;

    Ipc::Mem::RegisteredRunner::useConfig();
    initializeSessionCache();
#endif
}