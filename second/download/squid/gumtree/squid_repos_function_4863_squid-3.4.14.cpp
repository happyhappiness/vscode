static void
storeCossDirRebuild(CossSwapDir * sd)
{
    RebuildState *rb;
    int clean = 0;
    int zero = 0;
    FILE *fp;
    CBDATA_INIT_TYPE(RebuildState);
    rb = cbdataAlloc(RebuildState);
    rb->sd = sd;
    rb->speed = opt_foreground_rebuild ? 1 << 30 : 50;
    rb->flags.clean = (unsigned int) clean;
    /*
     * If the swap.state file exists in the cache_dir, then
     * we'll use storeCossRebuildFromSwapLog().
     */
    fp = storeCossDirOpenTmpSwapLog(sd, &clean, &zero);
    debugs(47, DBG_IMPORTANT, "Rebuilding COSS storage in " << sd->path << " (" << (clean ? "CLEAN" : "DIRTY") << ")");
    rb->log = fp;
    ++ StoreController::store_dirs_rebuilding;

    if (!clean || fp == NULL) {
        /* COSS cannot yet rebuild from a dirty state. If the log
         * is dirty then the COSS contents is thrown away.
         * Why? I guess it is because some contents will be lost,
         * and COSS cannot verify this..
         */

        if (fp != NULL)
            fclose(fp);

        /*
         * XXX Make sure we don't trigger an assertion if this is the first
         * storedir, since if we are, this call will cause storeRebuildComplete
         * to prematurely complete the rebuild process, and then some other
         * storedir will try to rebuild and eventually die.
         */
        eventAdd("storeCossRebuildComplete", storeCossRebuildComplete, rb, 0.0, 0);

        return;
    }

    eventAdd("storeCossRebuild", storeCossRebuildFromSwapLog, rb, 0.0, 1);
}