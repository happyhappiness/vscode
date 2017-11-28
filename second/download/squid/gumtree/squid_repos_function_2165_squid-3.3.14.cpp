static void
storeDigestRewriteResume(void)
{
    StoreEntry *e;

    assert(sd_state.rewrite_lock);
    assert(!sd_state.rebuild_lock);
    e = sd_state.rewrite_lock;
    sd_state.rewrite_offset = 0;
    EBIT_SET(e->flags, ENTRY_SPECIAL);
    /* setting public key will purge old digest entry if any */
    e->setPublicKey();
    /* fake reply */
    HttpReply *rep = new HttpReply;
    rep->setHeaders(HTTP_OK, "Cache Digest OK",
                    "application/cache-digest", (store_digest->mask_size + sizeof(sd_state.cblock)),
                    squid_curtime, (squid_curtime + Config.digest.rewrite_period) );
    debugs(71, 3, "storeDigestRewrite: entry expires on " << rep->expires <<
           " (" << std::showpos << (int) (rep->expires - squid_curtime) << ")");
    e->buffer();
    e->replaceHttpReply(rep);
    storeDigestCBlockSwapOut(e);
    e->flush();
    eventAdd("storeDigestSwapOutStep", storeDigestSwapOutStep, sd_state.rewrite_lock, 0.0, 1, false);
}