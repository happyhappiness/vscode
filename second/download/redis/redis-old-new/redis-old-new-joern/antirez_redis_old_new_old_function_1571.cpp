static bool
prof_dump(bool propagate_err, const char *filename, bool leakcheck)
{
	prof_tdata_t *prof_tdata;
	prof_cnt_t cnt_all;
	size_t tabind;
	union {
		prof_bt_t	*p;
		void		*v;
	} bt;
	union {
		prof_ctx_t	*p;
		void		*v;
	} ctx;
	size_t leak_nctx;

	cassert(config_prof);

	prof_tdata = prof_tdata_get();
	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
		return (true);
	prof_enter(prof_tdata);
	prof_dump_fd = creat(filename, 0644);
	if (prof_dump_fd == -1) {
		if (propagate_err == false) {
			malloc_printf(
			    "<jemalloc>: creat(\"%s\"), 0644) failed\n",
			    filename);
			if (opt_abort)
				abort();
		}
		goto label_error;
	}

	/* Merge per thread profile stats, and sum them in cnt_all. */
	memset(&cnt_all, 0, sizeof(prof_cnt_t));
	leak_nctx = 0;
	for (tabind = 0; ckh_iter(&bt2ctx, &tabind, NULL, &ctx.v) == false;)
		prof_ctx_sum(ctx.p, &cnt_all, &leak_nctx);

	/* Dump profile header. */
	if (opt_lg_prof_sample == 0) {
		if (prof_printf(propagate_err,
		    "heap profile: %"PRId64": %"PRId64
		    " [%"PRIu64": %"PRIu64"] @ heapprofile\n",
		    cnt_all.curobjs, cnt_all.curbytes,
		    cnt_all.accumobjs, cnt_all.accumbytes))
			goto label_error;
	} else {
		if (prof_printf(propagate_err,
		    "heap profile: %"PRId64": %"PRId64
		    " [%"PRIu64": %"PRIu64"] @ heap_v2/%"PRIu64"\n",
		    cnt_all.curobjs, cnt_all.curbytes,
		    cnt_all.accumobjs, cnt_all.accumbytes,
		    ((uint64_t)1U << opt_lg_prof_sample)))
			goto label_error;
	}

	/* Dump  per ctx profile stats. */
	for (tabind = 0; ckh_iter(&bt2ctx, &tabind, &bt.v, &ctx.v)
	    == false;) {
		if (prof_dump_ctx(propagate_err, ctx.p, bt.p))
			goto label_error;
	}

	/* Dump /proc/<pid>/maps if possible. */
	if (prof_dump_maps(propagate_err))
		goto label_error;

	if (prof_flush(propagate_err))
		goto label_error;
	close(prof_dump_fd);
	prof_leave(prof_tdata);

	if (leakcheck && cnt_all.curbytes != 0) {
		malloc_printf("<jemalloc>: Leak summary: %"PRId64" byte%s, %"
		    PRId64" object%s, %zu context%s\n",
		    cnt_all.curbytes, (cnt_all.curbytes != 1) ? "s" : "",
		    cnt_all.curobjs, (cnt_all.curobjs != 1) ? "s" : "",
		    leak_nctx, (leak_nctx != 1) ? "s" : "");
		malloc_printf(
		    "<jemalloc>: Run pprof on \"%s\" for leak detail\n",
		    filename);
	}

	return (false);
label_error:
	prof_leave(prof_tdata);
	return (true);
}