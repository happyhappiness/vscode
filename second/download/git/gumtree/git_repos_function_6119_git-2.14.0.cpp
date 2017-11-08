static int grep_submodule(struct grep_opt *opt, const struct object_id *oid,
			  const char *filename, const char *path)
{
	if (!is_submodule_active(the_repository, path))
		return 0;
	if (!is_submodule_populated_gently(path, NULL)) {
		/*
		 * If searching history, check for the presence of the
		 * submodule's gitdir before skipping the submodule.
		 */
		if (oid) {
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
		add_work(opt, GREP_SOURCE_SUBMODULE, filename, path, oid);
		return 0;
	} else
#endif
	{
		struct grep_source gs;
		int hit;

		grep_source_init(&gs, GREP_SOURCE_SUBMODULE,
				 filename, path, oid);
		hit = grep_submodule_launch(opt, &gs);

		grep_source_clear(&gs);
		return hit;
	}
}