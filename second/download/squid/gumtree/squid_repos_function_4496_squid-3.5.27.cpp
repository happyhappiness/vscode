void
SharedSessionCacheRr::create()
{
    if (!isSslServer()) //no need to configure ssl session cache.
        return;

    int items;
    items = Config.SSL.sessionCacheSize / sizeof(Ipc::MemMap::Slot);
    if (items)
        owner =  Ipc::MemMap::Init(SslSessionCacheName, items);
}