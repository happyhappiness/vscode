void
asnInit(void)
{
    static bool inited = false;
    squid_max_keylen = 40;

    if (!inited) {
        inited = true;
        squid_rn_init();
    }

    squid_rn_inithead(&AS_tree_head, 8);

    asnRegisterWithCacheManager();
}