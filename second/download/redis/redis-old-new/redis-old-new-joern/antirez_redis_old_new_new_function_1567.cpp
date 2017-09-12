static bool
prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, const prof_bt_t *bt,
    prof_ctx_list_t *ctx_ql)
{
	bool ret;
	unsigned i;

	cassert(config_prof);

	/*
	 * Current statistics can sum to 0 as a result of unmerged per thread
	 * statistics.  Additionally, interval- and growth-triggered dumps can
	 * occur between the time a ctx is created and when its statistics are
	 * filled in.  Avoid dumping any ctx that is an artifact of either
	 * implementation detail.
	 */
	malloc_mutex_lock(ctx->lock);
	if ((opt_prof_accum == false && ctx->cnt_summed.curobjs == 0) ||
	    (opt_prof_accum && ctx->cnt_summed.accumobjs == 0)) {
		assert(ctx->cnt_summed.curobjs == 0);
		assert(ctx->cnt_summed.curbytes == 0);
		assert(ctx->cnt_summed.accumobjs == 0);
		assert(ctx->cnt_summed.accumbytes == 0);
		ret = false;
		goto label_return;
	}

	if (prof_dump_printf(propagate_err, "%"PRId64": %"PRId64
	    " [%"PRIu64": %"PRIu64"] @",
	    ctx->cnt_summed.curobjs, ctx->cnt_summed.curbytes,
	    ctx->cnt_summed.accumobjs, ctx->cnt_summed.accumbytes)) {
		ret = true;
		goto label_return;
	}

	for (i = 0; i < bt->len; i++) {
		if (prof_dump_printf(propagate_err, " %#"PRIxPTR,
		    (uintptr_t)bt->vec[i])) {
			ret = true;
			goto label_return;
		}
	}

	if (prof_dump_write(propagate_err, "\n")) {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	prof_dump_ctx_cleanup_locked(ctx, ctx_ql);
	malloc_mutex_unlock(ctx->lock);
	return (ret);
}