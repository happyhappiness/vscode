	malloc_mutex_unlock(ctx->lock);
}

static void
prof_ctx_destroy(prof_ctx_t *ctx)
{
	prof_tdata_t *prof_tdata;

	cassert(config_prof);

	/*
	 * Check that ctx is still unused by any thread cache before destroying
	 * it.  prof_lookup() increments ctx->nlimbo in order to avoid a race
	 * condition with this function, as does prof_ctx_merge() in order to
	 * avoid a race between the main body of prof_ctx_merge() and entry
	 * into this function.
	 */
	prof_tdata = *prof_tdata_tsd_get();
	assert((uintptr_t)prof_tdata > (uintptr_t)PROF_TDATA_STATE_MAX);
	prof_enter(prof_tdata);
	malloc_mutex_lock(ctx->lock);
	if (ql_first(&ctx->cnts_ql) == NULL && ctx->cnt_merged.curobjs == 0 &&
	    ctx->nlimbo == 1) {
		assert(ctx->cnt_merged.curbytes == 0);
		assert(ctx->cnt_merged.accumobjs == 0);
		assert(ctx->cnt_merged.accumbytes == 0);
		/* Remove ctx from bt2ctx. */
		if (ckh_remove(&bt2ctx, ctx->bt, NULL, NULL))
			assert(false);
		prof_leave(prof_tdata);
		/* Destroy ctx. */
		malloc_mutex_unlock(ctx->lock);
		bt_destroy(ctx->bt);
		idalloc(ctx);
	} else {
		/*
		 * Compensate for increment in prof_ctx_merge() or
		 * prof_lookup().
		 */
		ctx->nlimbo--;
		malloc_mutex_unlock(ctx->lock);
		prof_leave(prof_tdata);
	}
}

static void
prof_ctx_merge(prof_ctx_t *ctx, prof_thr_cnt_t *cnt)
{
	bool destroy;

	cassert(config_prof);

	/* Merge cnt stats and detach from ctx. */
	malloc_mutex_lock(ctx->lock);
	ctx->cnt_merged.curobjs += cnt->cnts.curobjs;
	ctx->cnt_merged.curbytes += cnt->cnts.curbytes;
	ctx->cnt_merged.accumobjs += cnt->cnts.accumobjs;
	ctx->cnt_merged.accumbytes += cnt->cnts.accumbytes;
	ql_remove(&ctx->cnts_ql, cnt, cnts_link);
	if (opt_prof_accum == false && ql_first(&ctx->cnts_ql) == NULL &&
	    ctx->cnt_merged.curobjs == 0 && ctx->nlimbo == 0) {
		/*
		 * Increment ctx->nlimbo in order to keep another thread from
		 * winning the race to destroy ctx while this one has ctx->lock
		 * dropped.  Without this, it would be possible for another
		 * thread to:
		 *
		 * 1) Sample an allocation associated with ctx.
		 * 2) Deallocate the sampled object.
		 * 3) Successfully prof_ctx_destroy(ctx).
		 *
		 * The result would be that ctx no longer exists by the time
		 * this thread accesses it in prof_ctx_destroy().
		 */
		ctx->nlimbo++;
		destroy = true;
	} else
		destroy = false;
	malloc_mutex_unlock(ctx->lock);
	if (destroy)
		prof_ctx_destroy(ctx);
}

static bool
prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, prof_bt_t *bt)
{
	unsigned i;

	cassert(config_prof);
