static void
stats_arena_print(void (*write_cb)(void *, const char *), void *cbopaque,
    unsigned i, bool bins, bool large)
{
	unsigned nthreads;
	size_t page, pactive, pdirty, mapped;
	uint64_t npurge, nmadvise, purged;
	size_t small_allocated;
	uint64_t small_nmalloc, small_ndalloc, small_nrequests;
	size_t large_allocated;
	uint64_t large_nmalloc, large_ndalloc, large_nrequests;

	CTL_GET("arenas.page", &page, size_t);

	CTL_I_GET("stats.arenas.0.nthreads", &nthreads, unsigned);
	malloc_cprintf(write_cb, cbopaque,
	    "assigned threads: %u\n", nthreads);
	CTL_I_GET("stats.arenas.0.pactive", &pactive, size_t);
	CTL_I_GET("stats.arenas.0.pdirty", &pdirty, size_t);
	CTL_I_GET("stats.arenas.0.npurge", &npurge, uint64_t);
	CTL_I_GET("stats.arenas.0.nmadvise", &nmadvise, uint64_t);
	CTL_I_GET("stats.arenas.0.purged", &purged, uint64_t);
	malloc_cprintf(write_cb, cbopaque,
	    "dirty pages: %zu:%zu active:dirty, %"PRIu64" sweep%s,"
	    " %"PRIu64" madvise%s, %"PRIu64" purged\n",
	    pactive, pdirty, npurge, npurge == 1 ? "" : "s",
	    nmadvise, nmadvise == 1 ? "" : "s", purged);

	malloc_cprintf(write_cb, cbopaque,
	    "            allocated      nmalloc      ndalloc    nrequests\n");
	CTL_I_GET("stats.arenas.0.small.allocated", &small_allocated, size_t);
	CTL_I_GET("stats.arenas.0.small.nmalloc", &small_nmalloc, uint64_t);
	CTL_I_GET("stats.arenas.0.small.ndalloc", &small_ndalloc, uint64_t);
	CTL_I_GET("stats.arenas.0.small.nrequests", &small_nrequests, uint64_t);
	malloc_cprintf(write_cb, cbopaque,
	    "small:   %12zu %12"PRIu64" %12"PRIu64" %12"PRIu64"\n",
	    small_allocated, small_nmalloc, small_ndalloc, small_nrequests);
	CTL_I_GET("stats.arenas.0.large.allocated", &large_allocated, size_t);
	CTL_I_GET("stats.arenas.0.large.nmalloc", &large_nmalloc, uint64_t);
	CTL_I_GET("stats.arenas.0.large.ndalloc", &large_ndalloc, uint64_t);
	CTL_I_GET("stats.arenas.0.large.nrequests", &large_nrequests, uint64_t);
	malloc_cprintf(write_cb, cbopaque,
	    "large:   %12zu %12"PRIu64" %12"PRIu64" %12"PRIu64"\n",
	    large_allocated, large_nmalloc, large_ndalloc, large_nrequests);
	malloc_cprintf(write_cb, cbopaque,
	    "total:   %12zu %12"PRIu64" %12"PRIu64" %12"PRIu64"\n",
	    small_allocated + large_allocated,
	    small_nmalloc + large_nmalloc,
	    small_ndalloc + large_ndalloc,
	    small_nrequests + large_nrequests);
	malloc_cprintf(write_cb, cbopaque, "active:  %12zu\n", pactive * page);
	CTL_I_GET("stats.arenas.0.mapped", &mapped, size_t);
	malloc_cprintf(write_cb, cbopaque, "mapped:  %12zu\n", mapped);

	if (bins)
		stats_arena_bins_print(write_cb, cbopaque, i);
	if (large)
		stats_arena_lruns_print(write_cb, cbopaque, i);
}