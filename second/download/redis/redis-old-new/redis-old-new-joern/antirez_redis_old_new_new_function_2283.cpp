void
stats_print(void (*write_cb)(void *, const char *), void *cbopaque,
    const char *opts)
{
	int err;
	uint64_t epoch;
	size_t u64sz;
	bool general = true;
	bool merged = true;
	bool unmerged = true;
	bool bins = true;
	bool large = true;

	/*
	 * Refresh stats, in case mallctl() was called by the application.
	 *
	 * Check for OOM here, since refreshing the ctl cache can trigger
	 * allocation.  In practice, none of the subsequent mallctl()-related
	 * calls in this function will cause OOM if this one succeeds.
	 * */
	epoch = 1;
	u64sz = sizeof(uint64_t);
	err = je_mallctl("epoch", &epoch, &u64sz, &epoch, sizeof(uint64_t));
	if (err != 0) {
		if (err == EAGAIN) {
			malloc_write("<jemalloc>: Memory allocation failure in "
			    "mallctl(\"epoch\", ...)\n");
			return;
		}
		malloc_write("<jemalloc>: Failure in mallctl(\"epoch\", "
		    "...)\n");
		abort();
	}

	if (opts != NULL) {
		unsigned i;

		for (i = 0; opts[i] != '\0'; i++) {
			switch (opts[i]) {
			case 'g':
				general = false;
				break;
			case 'm':
				merged = false;
				break;
			case 'a':
				unmerged = false;
				break;
			case 'b':
				bins = false;
				break;
			case 'l':
				large = false;
				break;
			default:;
			}
		}
	}

	malloc_cprintf(write_cb, cbopaque,
	    "___ Begin jemalloc statistics ___\n");
	if (general) {
		int err;
		const char *cpv;
		bool bv;
		unsigned uv;
		ssize_t ssv;
		size_t sv, bsz, ssz, sssz, cpsz;

		bsz = sizeof(bool);
		ssz = sizeof(size_t);
		sssz = sizeof(ssize_t);
		cpsz = sizeof(const char *);

		CTL_GET("version", &cpv, const char *);
		malloc_cprintf(write_cb, cbopaque, "Version: %s\n", cpv);
		CTL_GET("config.debug", &bv, bool);
		malloc_cprintf(write_cb, cbopaque, "Assertions %s\n",
		    bv ? "enabled" : "disabled");

#define OPT_WRITE_BOOL(n)						\
		if ((err = je_mallctl("opt."#n, &bv, &bsz, NULL, 0))	\
		    == 0) {						\
			malloc_cprintf(write_cb, cbopaque,		\
			    "  opt."#n": %s\n", bv ? "true" : "false");	\
		}
#define OPT_WRITE_SIZE_T(n)						\
		if ((err = je_mallctl("opt."#n, &sv, &ssz, NULL, 0))	\
		    == 0) {						\
			malloc_cprintf(write_cb, cbopaque,		\
			"  opt."#n": %zu\n", sv);			\
		}
#define OPT_WRITE_SSIZE_T(n)						\
		if ((err = je_mallctl("opt."#n, &ssv, &sssz, NULL, 0))	\
		    == 0) {						\
			malloc_cprintf(write_cb, cbopaque,		\
			    "  opt."#n": %zd\n", ssv);			\
		}
#define OPT_WRITE_CHAR_P(n)						\
		if ((err = je_mallctl("opt."#n, &cpv, &cpsz, NULL, 0))	\
		    == 0) {						\
			malloc_cprintf(write_cb, cbopaque,		\
			    "  opt."#n": \"%s\"\n", cpv);		\
		}

		malloc_cprintf(write_cb, cbopaque,
		    "Run-time option settings:\n");
		OPT_WRITE_BOOL(abort)
		OPT_WRITE_SIZE_T(lg_chunk)
		OPT_WRITE_CHAR_P(dss)
		OPT_WRITE_SIZE_T(narenas)
		OPT_WRITE_SSIZE_T(lg_dirty_mult)
		OPT_WRITE_BOOL(stats_print)
		OPT_WRITE_BOOL(junk)
		OPT_WRITE_SIZE_T(quarantine)
		OPT_WRITE_BOOL(redzone)
		OPT_WRITE_BOOL(zero)
		OPT_WRITE_BOOL(utrace)
		OPT_WRITE_BOOL(valgrind)
		OPT_WRITE_BOOL(xmalloc)
		OPT_WRITE_BOOL(tcache)
		OPT_WRITE_SSIZE_T(lg_tcache_max)
		OPT_WRITE_BOOL(prof)
		OPT_WRITE_CHAR_P(prof_prefix)
		OPT_WRITE_BOOL(prof_active)
		OPT_WRITE_SSIZE_T(lg_prof_sample)
		OPT_WRITE_BOOL(prof_accum)
		OPT_WRITE_SSIZE_T(lg_prof_interval)
		OPT_WRITE_BOOL(prof_gdump)
		OPT_WRITE_BOOL(prof_final)
		OPT_WRITE_BOOL(prof_leak)

#undef OPT_WRITE_BOOL
#undef OPT_WRITE_SIZE_T
#undef OPT_WRITE_SSIZE_T
#undef OPT_WRITE_CHAR_P

		malloc_cprintf(write_cb, cbopaque, "CPUs: %u\n", ncpus);

		CTL_GET("arenas.narenas", &uv, unsigned);
		malloc_cprintf(write_cb, cbopaque, "Arenas: %u\n", uv);

		malloc_cprintf(write_cb, cbopaque, "Pointer size: %zu\n",
		    sizeof(void *));

		CTL_GET("arenas.quantum", &sv, size_t);
		malloc_cprintf(write_cb, cbopaque, "Quantum size: %zu\n", sv);

		CTL_GET("arenas.page", &sv, size_t);
		malloc_cprintf(write_cb, cbopaque, "Page size: %zu\n", sv);

		CTL_GET("opt.lg_dirty_mult", &ssv, ssize_t);
		if (ssv >= 0) {
			malloc_cprintf(write_cb, cbopaque,
			    "Min active:dirty page ratio per arena: %u:1\n",
			    (1U << ssv));
		} else {
			malloc_cprintf(write_cb, cbopaque,
			    "Min active:dirty page ratio per arena: N/A\n");
		}
		if ((err = je_mallctl("arenas.tcache_max", &sv, &ssz, NULL, 0))
		    == 0) {
			malloc_cprintf(write_cb, cbopaque,
			    "Maximum thread-cached size class: %zu\n", sv);
		}
		if ((err = je_mallctl("opt.prof", &bv, &bsz, NULL, 0)) == 0 &&
		    bv) {
			CTL_GET("opt.lg_prof_sample", &sv, size_t);
			malloc_cprintf(write_cb, cbopaque,
			    "Average profile sample interval: %"PRIu64
			    " (2^%zu)\n", (((uint64_t)1U) << sv), sv);

			CTL_GET("opt.lg_prof_interval", &ssv, ssize_t);
			if (ssv >= 0) {
				malloc_cprintf(write_cb, cbopaque,
				    "Average profile dump interval: %"PRIu64
				    " (2^%zd)\n",
				    (((uint64_t)1U) << ssv), ssv);
			} else {
				malloc_cprintf(write_cb, cbopaque,
				    "Average profile dump interval: N/A\n");
			}
		}
		CTL_GET("opt.lg_chunk", &sv, size_t);
		malloc_cprintf(write_cb, cbopaque, "Chunk size: %zu (2^%zu)\n",
		    (ZU(1) << sv), sv);
	}

	if (config_stats) {
		size_t *cactive;
		size_t allocated, active, mapped;
		size_t chunks_current, chunks_high;
		uint64_t chunks_total;
		size_t huge_allocated;
		uint64_t huge_nmalloc, huge_ndalloc;

		CTL_GET("stats.cactive", &cactive, size_t *);
		CTL_GET("stats.allocated", &allocated, size_t);
		CTL_GET("stats.active", &active, size_t);
		CTL_GET("stats.mapped", &mapped, size_t);
		malloc_cprintf(write_cb, cbopaque,
		    "Allocated: %zu, active: %zu, mapped: %zu\n",
		    allocated, active, mapped);
		malloc_cprintf(write_cb, cbopaque,
		    "Current active ceiling: %zu\n", atomic_read_z(cactive));

		/* Print chunk stats. */
		CTL_GET("stats.chunks.total", &chunks_total, uint64_t);
		CTL_GET("stats.chunks.high", &chunks_high, size_t);
		CTL_GET("stats.chunks.current", &chunks_current, size_t);
		malloc_cprintf(write_cb, cbopaque, "chunks: nchunks   "
		    "highchunks    curchunks\n");
		malloc_cprintf(write_cb, cbopaque,
		    "  %13"PRIu64" %12zu %12zu\n",
		    chunks_total, chunks_high, chunks_current);

		/* Print huge stats. */
		CTL_GET("stats.huge.nmalloc", &huge_nmalloc, uint64_t);
		CTL_GET("stats.huge.ndalloc", &huge_ndalloc, uint64_t);
		CTL_GET("stats.huge.allocated", &huge_allocated, size_t);
		malloc_cprintf(write_cb, cbopaque,
		    "huge: nmalloc      ndalloc    allocated\n");
		malloc_cprintf(write_cb, cbopaque,
		    " %12"PRIu64" %12"PRIu64" %12zu\n",
		    huge_nmalloc, huge_ndalloc, huge_allocated);

		if (merged) {
			unsigned narenas;

			CTL_GET("arenas.narenas", &narenas, unsigned);
			{
				VARIABLE_ARRAY(bool, initialized, narenas);
				size_t isz;
				unsigned i, ninitialized;

				isz = sizeof(bool) * narenas;
				xmallctl("arenas.initialized", initialized,
				    &isz, NULL, 0);
				for (i = ninitialized = 0; i < narenas; i++) {
					if (initialized[i])
						ninitialized++;
				}

				if (ninitialized > 1 || unmerged == false) {
					/* Print merged arena stats. */
					malloc_cprintf(write_cb, cbopaque,
					    "\nMerged arenas stats:\n");
					stats_arena_print(write_cb, cbopaque,
					    narenas, bins, large);
				}
			}
		}

		if (unmerged) {
			unsigned narenas;

			/* Print stats for each arena. */

			CTL_GET("arenas.narenas", &narenas, unsigned);
			{
				VARIABLE_ARRAY(bool, initialized, narenas);
				size_t isz;
				unsigned i;

				isz = sizeof(bool) * narenas;
				xmallctl("arenas.initialized", initialized,
				    &isz, NULL, 0);

				for (i = 0; i < narenas; i++) {
					if (initialized[i]) {
						malloc_cprintf(write_cb,
						    cbopaque,
						    "\narenas[%u]:\n", i);
						stats_arena_print(write_cb,
						    cbopaque, i, bins, large);
					}
				}
			}
		}
	}
	malloc_cprintf(write_cb, cbopaque, "--- End jemalloc statistics ---\n");
}