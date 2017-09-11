		CTL_GET("stats.chunks.current", &chunks_current, size_t);
		malloc_cprintf(write_cb, cbopaque, "chunks: nchunks   "
		    "highchunks    curchunks\n");
		malloc_cprintf(write_cb, cbopaque,
		    "  %13"PRIu64" %12zu %12zu\n",
		    chunks_total, chunks_high, chunks_current);

		/* Print huge stats. */
