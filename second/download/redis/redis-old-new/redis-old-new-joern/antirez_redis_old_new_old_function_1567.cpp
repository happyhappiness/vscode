static bool
prof_dump_ctx(bool propagate_err, prof_ctx_t *ctx, prof_bt_t *bt)
{
	unsigned i;

	cassert(config_prof);

	/*
	 * Current statistics can sum to 0 as a result of unmerged per thread
	 * statistics.  Additionally, interval- and growth-triggered dumps can
	 * occur between the time a ctx is created and when its statistics are
	 * filled in.  Avoid dumping any ctx that is an artifact of either
	 * implementation detail.
	 */
	if ((opt_prof_accum == false && ctx->cnt_summed.curobjs == 0) ||
	    (opt_prof_accum && ctx->cnt_summed.accumobjs == 0)) {
		assert(ctx->cnt_summed.curobjs == 0);
		assert(ctx->cnt_summed.curbytes == 0);
		assert(ctx->cnt_summed.accumobjs == 0);
		assert(ctx->cnt_summed.accumbytes == 0);
		return (false);
	}

	if (prof_printf(propagate_err, "%"PRId64": %"PRId64
	    " [%"PRIu64": %"PRIu64"] @",
	    ctx->cnt_summed.curobjs, ctx->cnt_summed.curbytes,
	    ctx->cnt_summed.accumobjs, ctx->cnt_summed.accumbytes))
		return (true);

	for (i = 0; i < bt->len; i++) {
		if (prof_printf(propagate_err, " %#"PRIxPTR,
		    (uintptr_t)bt->vec[i]))
			return (true);
	}

	if (prof_write(propagate_err, "\n"))
		return (true);

	return (false);
}