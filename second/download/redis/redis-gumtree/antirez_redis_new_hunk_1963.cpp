	malloc_mutex_unlock(ctx->lock);
}

static bool
prof_dump_header(bool propagate_err, const prof_cnt_t *cnt_all)
{

	if (opt_lg_prof_sample == 0) {
		if (prof_dump_printf(propagate_err,
		    "heap profile: %"PRId64": %"PRId64
		    " [%"PRIu64": %"PRIu64"] @ heapprofile\n",
		    cnt_all->curobjs, cnt_all->curbytes,
		    cnt_all->accumobjs, cnt_all->accumbytes))
			return (true);
	} else {
		if (prof_dump_printf(propagate_err,
		    "heap profile: %"PRId64": %"PRId64
		    " [%"PRIu64": %"PRIu64"] @ heap_v2/%"PRIu64"\n",
		    cnt_all->curobjs, cnt_all->curbytes,
		    cnt_all->accumobjs, cnt_all->accumbytes,
		    ((uint64_t)1U << opt_lg_prof_sample)))
			return (true);
	}

	return (false);
}

static void
prof_dump_ctx_cleanup_locked(prof_ctx_t *ctx, prof_ctx_list_t *ctx_ql)
{

	ctx->nlimbo--;
	ql_remove(ctx_ql, ctx, dump_link);
}

static void
prof_dump_ctx_cleanup(prof_ctx_t *ctx, prof_ctx_list_t *ctx_ql)
{

	malloc_mutex_lock(ctx->lock);
	prof_dump_ctx_cleanup_locked(ctx, ctx_ql);
	malloc_mutex_unlock(ctx->lock);
}

static bool
prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, const prof_bt_t *bt,
    prof_ctx_list_t *ctx_ql)
{
	bool ret;
	unsigned i;

	cassert(config_prof);
