	va_start(ap, format);
	malloc_vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);
	ret = prof_write(propagate_err, buf);

	return (ret);
}

static void
prof_ctx_sum(prof_ctx_t *ctx, prof_cnt_t *cnt_all, size_t *leak_nctx)
{
	prof_thr_cnt_t *thr_cnt;
	prof_cnt_t tcnt;
