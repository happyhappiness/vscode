	prof_cnt_t cnt_all;
	size_t tabind;
	union {
		prof_ctx_t	*p;
		void		*v;
	} ctx;
	size_t leak_nctx;
	prof_ctx_list_t ctx_ql;

	cassert(config_prof);

	prof_tdata = prof_tdata_get(false);
	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
		return (true);

	malloc_mutex_lock(&prof_dump_mtx);

	/* Merge per thread profile stats, and sum them in cnt_all. */
	memset(&cnt_all, 0, sizeof(prof_cnt_t));
	leak_nctx = 0;
	ql_new(&ctx_ql);
	prof_enter(prof_tdata);
	for (tabind = 0; ckh_iter(&bt2ctx, &tabind, NULL, &ctx.v) == false;)
		prof_dump_ctx_prep(ctx.p, &cnt_all, &leak_nctx, &ctx_ql);
	prof_leave(prof_tdata);

	/* Create dump file. */
	if ((prof_dump_fd = prof_dump_open(propagate_err, filename)) == -1)
		goto label_open_close_error;

	/* Dump profile header. */
	if (prof_dump_header(propagate_err, &cnt_all))
		goto label_write_error;

	/* Dump per ctx profile stats. */
	while ((ctx.p = ql_first(&ctx_ql)) != NULL) {
		if (prof_dump_ctx(propagate_err, ctx.p, ctx.p->bt, &ctx_ql))
			goto label_write_error;
	}

	/* Dump /proc/<pid>/maps if possible. */
	if (prof_dump_maps(propagate_err))
		goto label_write_error;

	if (prof_dump_close(propagate_err))
		goto label_open_close_error;

	malloc_mutex_unlock(&prof_dump_mtx);

	if (leakcheck)
		prof_leakcheck(&cnt_all, leak_nctx, filename);

	return (false);
label_write_error:
	prof_dump_close(propagate_err);
label_open_close_error:
	while ((ctx.p = ql_first(&ctx_ql)) != NULL)
		prof_dump_ctx_cleanup(ctx.p, &ctx_ql);
	malloc_mutex_unlock(&prof_dump_mtx);
	return (true);
}

#define	DUMP_FILENAME_BUFSIZE	(PATH_MAX + 1)
#define	VSEQ_INVALID		UINT64_C(0xffffffffffffffff)
static void
prof_dump_filename(char *filename, char v, int64_t vseq)
{

	cassert(config_prof);

	if (vseq != VSEQ_INVALID) {
	        /* "<prefix>.<pid>.<seq>.v<vseq>.heap" */
		malloc_snprintf(filename, DUMP_FILENAME_BUFSIZE,
		    "%s.%d.%"PRIu64".%c%"PRId64".heap",
