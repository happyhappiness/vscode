static int check_repository_format_gently(const char *gitdir, int *nongit_ok)
{
	struct strbuf sb = STRBUF_INIT;
	struct strbuf err = STRBUF_INIT;
	struct repository_format candidate;
	int has_common;

	has_common = get_common_dir(&sb, gitdir);
	strbuf_addstr(&sb, "/config");
	read_repository_format(&candidate, sb.buf);
	strbuf_release(&sb);

	/*
	 * For historical use of check_repository_format() in git-init,
	 * we treat a missing config as a silent "ok", even when nongit_ok
	 * is unset.
	 */
	if (candidate.version < 0)
		return 0;

	if (verify_repository_format(&candidate, &err) < 0) {
		if (nongit_ok) {
			warning("%s", err.buf);
			strbuf_release(&err);
			*nongit_ok = -1;
			return -1;
		}
		die("%s", err.buf);
	}

	repository_format_precious_objects = candidate.precious_objects;
	string_list_clear(&candidate.unknown_extensions, 0);
	if (!has_common) {
		if (candidate.is_bare != -1) {
			is_bare_repository_cfg = candidate.is_bare;
			if (is_bare_repository_cfg == 1)
				inside_work_tree = -1;
		}
		if (candidate.work_tree) {
			free(git_work_tree_cfg);
			git_work_tree_cfg = candidate.work_tree;
			inside_work_tree = -1;
		}
	} else {
		free(candidate.work_tree);
	}

	return 0;
}