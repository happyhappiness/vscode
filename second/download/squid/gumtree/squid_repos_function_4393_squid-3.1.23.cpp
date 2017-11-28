void
asnInit(void)
{
    static int inited = 0;
    squid_max_keylen = 40;
    CBDATA_INIT_TYPE(ASState);

    if (0 == inited++)
        squid_rn_init();

    squid_rn_inithead(&AS_tree_head, 8);

    asnRegisterWithCacheManager();
}