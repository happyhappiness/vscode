	return (ret.p);
}

#ifdef JEMALLOC_JET
size_t
prof_bt_count(void)
{
	size_t bt_count;
	prof_tdata_t *prof_tdata;

	prof_tdata = prof_tdata_get(false);
	if ((uintptr_t)prof_tdata <= (uintptr_t)PROF_TDATA_STATE_MAX)
		return (0);

	prof_enter(prof_tdata);
	bt_count = ckh_count(&bt2ctx);
	prof_leave(prof_tdata);

	return (bt_count);
}
#endif

#ifdef JEMALLOC_JET
#undef prof_dump_open
#define	prof_dump_open JEMALLOC_N(prof_dump_open_impl)
#endif
static int
prof_dump_open(bool propagate_err, const char *filename)
{
	int fd;

	fd = creat(filename, 0644);
	if (fd == -1 && propagate_err == false) {
		malloc_printf("<jemalloc>: creat(\"%s\"), 0644) failed\n",
		    filename);
		if (opt_abort)
			abort();
	}

	return (fd);
}
#ifdef JEMALLOC_JET
#undef prof_dump_open
#define	prof_dump_open JEMALLOC_N(prof_dump_open)
prof_dump_open_t *prof_dump_open = JEMALLOC_N(prof_dump_open_impl);
#endif

static bool
prof_dump_flush(bool propagate_err)
{
	bool ret = false;
	ssize_t err;
