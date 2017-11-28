void
storeDigestInit(void)
{
    storeDigestRegisterWithCacheManager();

#if USE_CACHE_DIGESTS
    const int cap = storeDigestCalcCap();

    if (!Config.onoff.digest_generation) {
        store_digest = NULL;
        debugs(71, 3, "Local cache digest generation disabled");
        return;
    }

    store_digest = cacheDigestCreate(cap, Config.digest.bits_per_entry);
    debugs(71, DBG_IMPORTANT, "Local cache digest enabled; rebuild/rewrite every " <<
           (int) Config.digest.rebuild_period << "/" <<
           (int) Config.digest.rewrite_period << " sec");

    memset(&sd_state, 0, sizeof(sd_state));
#else
    store_digest = NULL;
    debugs(71, 3, "Local cache digest is 'off'");
#endif
}