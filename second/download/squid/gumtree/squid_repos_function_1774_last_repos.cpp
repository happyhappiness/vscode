void
storeDigestInit(void)
{
    Mgr::RegisterAction("store_digest", "Store Digest", storeDigestReport, 0, 1);

#if USE_CACHE_DIGESTS
    if (!Config.onoff.digest_generation) {
        store_digest = NULL;
        debugs(71, 3, "Local cache digest generation disabled");
        return;
    }

    const uint64_t cap = storeDigestCalcCap();
    store_digest = new CacheDigest(cap, Config.digest.bits_per_entry);
    debugs(71, DBG_IMPORTANT, "Local cache digest enabled; rebuild/rewrite every " <<
           (int) Config.digest.rebuild_period << "/" <<
           (int) Config.digest.rewrite_period << " sec");

    memset(&sd_state, 0, sizeof(sd_state));
#else
    store_digest = NULL;
    debugs(71, 3, "Local cache digest is 'off'");
#endif
}