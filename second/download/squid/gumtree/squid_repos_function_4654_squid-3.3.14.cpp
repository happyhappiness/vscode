void
asnInit(void)
{
    static bool inited = false;
    squid_max_keylen = 40;
    CBDATA_INIT_TYPE(ASState);

    if (!inited) {
        inited = true;
        squid_rn_init();
    }

    squid_rn_inithead(&AS_tree_head, 8);

    asnRegisterWithCacheManager();
}