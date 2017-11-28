void ClientDelayConfig::clean()
{
    for (unsigned int i = 0; i < pools.size(); ++i) {
        aclDestroyAccessList(&pools[i].access);
    }
}