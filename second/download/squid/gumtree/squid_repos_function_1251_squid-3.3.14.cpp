void
Mem::Report(std::ostream &stream)
{
    static char buf[64];
    static MemPoolStats mp_stats;
    static MemPoolGlobalStats mp_total;
    int not_used = 0;
    MemPoolIterator *iter;
    MemAllocator *pool;

    /* caption */
    stream << "Current memory usage:\n";
    /* heading */
    stream << "Pool\t Obj Size\t"
    "Chunks\t\t\t\t\t\t\t"
    "Allocated\t\t\t\t\t"
    "In Use\t\t\t\t\t"
    "Idle\t\t\t"
    "Allocations Saved\t\t\t"
    "Rate\t"
    "\n"
    " \t (bytes)\t"
    "KB/ch\t obj/ch\t"
    "(#)\t used\t free\t part\t %Frag\t "
    "(#)\t (KB)\t high (KB)\t high (hrs)\t %Tot\t"
    "(#)\t (KB)\t high (KB)\t high (hrs)\t %alloc\t"
    "(#)\t (KB)\t high (KB)\t"
    "(#)\t %cnt\t %vol\t"
    "(#)/sec\t"
    "\n";
    xm_deltat = current_dtime - xm_time;
    xm_time = current_dtime;

    /* Get stats for Totals report line */
    memPoolGetGlobalStats(&mp_total);

    MemPoolStats *sortme = (MemPoolStats *) xcalloc(mp_total.tot_pools_alloc ,sizeof(*sortme));
    int npools = 0;

    /* main table */
    iter = memPoolIterate();

    while ((pool = memPoolIterateNext(iter))) {
        pool->getStats(&mp_stats);

        if (!mp_stats.pool)	/* pool destroyed */
            continue;

        if (mp_stats.pool->getMeter().gb_allocated.count > 0) {
            /* this pool has been used */
            sortme[npools] = mp_stats;
            ++npools;
        } else {
            ++not_used;
        }
    }

    memPoolIterateDone(&iter);

    qsort(sortme, npools, sizeof(*sortme), MemPoolReportSorter);

    for (int i = 0; i< npools; ++i) {
        PoolReport(&sortme[i], mp_total.TheMeter, stream);
    }

    xfree(sortme);

    mp_stats.pool = NULL;
    mp_stats.label = "Total";
    mp_stats.meter = mp_total.TheMeter;
    mp_stats.obj_size = 1;
    mp_stats.chunk_capacity = 0;
    mp_stats.chunk_size = 0;
    mp_stats.chunks_alloc = mp_total.tot_chunks_alloc;
    mp_stats.chunks_inuse = mp_total.tot_chunks_inuse;
    mp_stats.chunks_partial = mp_total.tot_chunks_partial;
    mp_stats.chunks_free = mp_total.tot_chunks_free;
    mp_stats.items_alloc = mp_total.tot_items_alloc;
    mp_stats.items_inuse = mp_total.tot_items_inuse;
    mp_stats.items_idle = mp_total.tot_items_idle;
    mp_stats.overhead = mp_total.tot_overhead;

    PoolReport(&mp_stats, mp_total.TheMeter, stream);

    /* Cumulative */
    stream << "Cumulative allocated volume: "<< double_to_str(buf, 64, mp_total.TheMeter->gb_allocated.bytes) << "\n";
    /* overhead */
    stream << "Current overhead: " << mp_total.tot_overhead << " bytes (" <<
    std::setprecision(3) << xpercent(mp_total.tot_overhead, mp_total.TheMeter->inuse.level) << "%)\n";
    /* limits */
    if (mp_total.mem_idle_limit >= 0)
        stream << "Idle pool limit: " << std::setprecision(2) << toMB(mp_total.mem_idle_limit) << " MB\n";
    /* limits */
    stream << "Total Pools created: " << mp_total.tot_pools_alloc << "\n";
    stream << "Pools ever used:     " << mp_total.tot_pools_alloc - not_used << " (shown above)\n";
    stream << "Currently in use:    " << mp_total.tot_pools_inuse << "\n";
}