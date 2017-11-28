void
externalAclInit(void)
{
    static int firstTimeInit = 1;
    external_acl *p;

    for (p = Config.externalAclHelperList; p; p = p->next) {
        if (!p->cache)
            p->cache = hash_create((HASHCMP *) strcmp, hashPrime(1024), hash4);

        if (!p->theHelper)
            p->theHelper = helperCreate(p->name);

        p->theHelper->cmdline = p->cmdline;

        p->theHelper->n_to_start = p->children;

        p->theHelper->concurrency = p->concurrency;

        p->theHelper->ipc_type = IPC_TCP_SOCKET;

        p->theHelper->addr = p->local_addr;

        helperOpenServers(p->theHelper);
    }

    if (firstTimeInit) {
        firstTimeInit = 0;
        CBDATA_INIT_TYPE_FREECB(externalAclState, free_externalAclState);
    }

    externalAclRegisterWithCacheManager();
}