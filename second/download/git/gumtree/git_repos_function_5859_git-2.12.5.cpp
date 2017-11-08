static int grep_submodule(struct grep_opt *opt, const unsigned char *sha1,
			  const char *filename, const char *path)
{
	if (!is_submodule_initialized(path))
		return 0;
	if (!is_submodule_populated(path)) {
		/*
		 * If searching history, check for the presense of the
		 * submodule's gitdir before skipping the submodule.
		 */
		if (sha1) {
			const struct submodule *sub =
					submodule_from_path(null_sha1, path);
			if (sub)
				path = git_path("modules/%s", sub->name);

			if (!(is_directory(path) && is_git_directory(path)))
				return 0;
		} else {
			return 0;
		}
	}

#ifndef NO_PTHREADS
	if (num_threads) {
		add_work(opt, GREP_SOURCE_SUBMODULE, filename, path, sha1);
		return 0;
	} else
#endif
	{
		struct work_item w;
		int hit;

		grep_source_init(&w.source, GREP_SOURCE_SUBMODULE,
				 filename, path, sha1);
		strbuf_init(&w.out, 0);
		opt->output_priv = &w;
		hit = grep_submodule_launch(opt, &w.source);

		write_or_die(1, w.out.buf, w.out.len);

		grep_source_clear(&w.source);
		strbuf_release(&w.out);
		return hit;
	}
}