	CTL_I_GET("stats.arenas.0.nthreads", &nthreads, unsigned);
	malloc_cprintf(write_cb, cbopaque,
	    "assigned threads: %u\n", nthreads);
	CTL_I_GET("stats.arenas.0.dss", &dss, const char *);
	malloc_cprintf(write_cb, cbopaque, "dss allocation precedence: %s\n",
	    dss);
	CTL_I_GET("stats.arenas.0.pactive", &pactive, size_t);
	CTL_I_GET("stats.arenas.0.pdirty", &pdirty, size_t);
	CTL_I_GET("stats.arenas.0.npurge", &npurge, uint64_t);
