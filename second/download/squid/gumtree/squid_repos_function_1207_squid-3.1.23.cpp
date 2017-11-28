void
memClean(void)
{
    MemPoolGlobalStats stats;
    MemPools::GetInstance().setIdleLimit(0);
    MemPools::GetInstance().clean(0);
    memPoolGetGlobalStats(&stats);

    if (stats.tot_items_inuse)
        debugs(13, 2, "memCleanModule: " << stats.tot_items_inuse <<
               " items in " << stats.tot_chunks_inuse << " chunks and " <<
               stats.tot_pools_inuse << " pools are left dirty");
}