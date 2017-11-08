static int git_index_pack_config(const char *k, const char *v, void *cb)
{
	struct pack_idx_option *opts = cb;

	if (!strcmp(k, "pack.indexversion")) {
		opts->version = git_config_int(k, v);
		if (opts->version > 2)
			die(_("bad pack.indexversion=%"PRIu32), opts->version);
		return 0;
	}
	if (!strcmp(k, "pack.threads")) {
		nr_threads = git_config_int(k, v);
		if (nr_threads < 0)
			die(_("invalid number of threads specified (%d)"),
			    nr_threads);
#ifdef NO_PTHREADS
		if (nr_threads != 1)
			warning(_("no threads support, ignoring %s"), k);
		nr_threads = 1;
#endif
		return 0;
	}
	return git_default_config(k, v, cb);
}