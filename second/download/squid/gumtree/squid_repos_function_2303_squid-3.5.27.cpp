static void
storeDigestRewriteFinish(StoreEntry * e)
{
    assert(e == sd_state.rewrite_lock);
    e->complete();
    e->timestampsSet();
    debugs(71, 2, "storeDigestRewriteFinish: digest expires at " << e->expires <<
           " (" << std::showpos << (int) (e->expires - squid_curtime) << ")");
    /* is this the write order? @?@ */
    e->mem_obj->unlinkRequest();
    e->unlock("storeDigestRewriteFinish");
    sd_state.rewrite_lock = NULL;
    ++sd_state.rewrite_count;
    eventAdd("storeDigestRewriteStart", storeDigestRewriteStart, NULL, (double)
             Config.digest.rewrite_period, 1);
    /* resume pending Rebuild if any */

    if (sd_state.rebuild_lock)
        storeDigestRebuildResume();
}