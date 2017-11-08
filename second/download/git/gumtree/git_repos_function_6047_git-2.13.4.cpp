static int grep_submodule(struct grep_opt *opt, const unsigned char *sha1,
			  const char *filename, const char *path)
{
	if (!is_submodule_initialized(path))
		return 0;
	if (!is_submodule_populated_gently(path, NULL)) {
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
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_SUBMODULE,
				 filename, path, sha1);
		hit = grep_submodule_launch(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
}