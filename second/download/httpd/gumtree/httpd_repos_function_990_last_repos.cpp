void ssl_scache_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->sesscache) {
        mc->sesscache->destroy(mc->sesscache_context, s);
    }

#ifdef HAVE_OCSP_STAPLING
    if (mc->stapling_cache) {
        mc->stapling_cache->destroy(mc->stapling_cache_context, s);
    }
#endif

}