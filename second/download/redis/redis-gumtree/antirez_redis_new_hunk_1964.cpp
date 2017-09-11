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

static bool
prof_dump_maps(bool propagate_err)
{
	bool ret;
	int mfd;
	char filename[PATH_MAX + 1];

	cassert(config_prof);
#ifdef __FreeBSD__
	malloc_snprintf(filename, sizeof(filename), "/proc/curproc/map");
#else
	malloc_snprintf(filename, sizeof(filename), "/proc/%d/maps",
	    (int)getpid());
#endif
	mfd = open(filename, O_RDONLY);
	if (mfd != -1) {
		ssize_t nread;

		if (prof_dump_write(propagate_err, "\nMAPPED_LIBRARIES:\n") &&
		    propagate_err) {
			ret = true;
			goto label_return;
		}
		nread = 0;
		do {
			prof_dump_buf_end += nread;
			if (prof_dump_buf_end == PROF_DUMP_BUFSIZE) {
				/* Make space in prof_dump_buf before read(). */
				if (prof_dump_flush(propagate_err) &&
				    propagate_err) {
					ret = true;
					goto label_return;
				}
			}
			nread = read(mfd, &prof_dump_buf[prof_dump_buf_end],
			    PROF_DUMP_BUFSIZE - prof_dump_buf_end);
		} while (nread > 0);
	} else {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	if (mfd != -1)
		close(mfd);
	return (ret);
}

static void
prof_leakcheck(const prof_cnt_t *cnt_all, size_t leak_nctx,
    const char *filename)
{

	if (cnt_all->curbytes != 0) {
		malloc_printf("<jemalloc>: Leak summary: %"PRId64" byte%s, %"
		    PRId64" object%s, %zu context%s\n",
		    cnt_all->curbytes, (cnt_all->curbytes != 1) ? "s" : "",
		    cnt_all->curobjs, (cnt_all->curobjs != 1) ? "s" : "",
		    leak_nctx, (leak_nctx != 1) ? "s" : "");
		malloc_printf(
		    "<jemalloc>: Run pprof on \"%s\" for leak detail\n",
		    filename);
	}
}

static bool
