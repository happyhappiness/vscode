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

static bool
prof_dump_maps(bool propagate_err)
{
	int mfd;
	char filename[PATH_MAX + 1];

	cassert(config_prof);

	malloc_snprintf(filename, sizeof(filename), "/proc/%d/maps",
	    (int)getpid());
	mfd = open(filename, O_RDONLY);
	if (mfd != -1) {
		ssize_t nread;

		if (prof_write(propagate_err, "\nMAPPED_LIBRARIES:\n") &&
		    propagate_err)
			return (true);
		nread = 0;
		do {
			prof_dump_buf_end += nread;
			if (prof_dump_buf_end == PROF_DUMP_BUFSIZE) {
				/* Make space in prof_dump_buf before read(). */
				if (prof_flush(propagate_err) && propagate_err)
					return (true);
			}
			nread = read(mfd, &prof_dump_buf[prof_dump_buf_end],
			    PROF_DUMP_BUFSIZE - prof_dump_buf_end);
		} while (nread > 0);
		close(mfd);
	} else
		return (true);

	return (false);
}

static bool
