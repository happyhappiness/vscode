static void
storeDigestRewriteStart(void *datanotused)
{
    RequestFlags flags;
    char *url;
    StoreEntry *e;

    assert(store_digest);
    /* prevent overlapping if rewrite schedule is too tight */

    if (sd_state.rewrite_lock) {
        debugs(71, DBG_IMPORTANT, "storeDigestRewrite: overlap detected, consider increasing rewrite period");
        return;
    }

    debugs(71, 2, "storeDigestRewrite: start rewrite #" << sd_state.rewrite_count + 1);
    /* make new store entry */
    url = internalLocalUri("/squid-internal-periodic/", StoreDigestFileName);
    flags.cachable = 1;
    e = storeCreateEntry(url, url, flags, METHOD_GET);
    assert(e);
    sd_state.rewrite_lock = e;
    debugs(71, 3, "storeDigestRewrite: url: " << url << " key: " << e->getMD5Text());
    HttpRequest *req = HttpRequest::CreateFromUrl(url);
    e->mem_obj->request = HTTPMSGLOCK(req);
    /* wait for rebuild (if any) to finish */

    if (sd_state.rebuild_lock) {
        debugs(71, 2, "storeDigestRewriteStart: waiting for rebuild to finish.");
        return;
    }

    storeDigestRewriteResume();
}