static int git_merge_config(const char *k, const char *v, void *cb)
{
	int status;

	if (branch && starts_with(k, "branch.") &&
		starts_with(k + 7, branch) &&
		!strcmp(k + 7 + strlen(branch), ".mergeoptions")) {
		free(branch_mergeoptions);
		branch_mergeoptions = xstrdup(v);
		return 0;
	}

	if (!strcmp(k, "merge.diffstat") || !strcmp(k, "merge.stat"))
		show_diffstat = git_config_bool(k, v);
	else if (!strcmp(k, "pull.twohead"))
		return git_config_string(&pull_twohead, k, v);
	else if (!strcmp(k, "pull.octopus"))
		return git_config_string(&pull_octopus, k, v);
	else if (!strcmp(k, "merge.renormalize"))
		option_renormalize = git_config_bool(k, v);
	else if (!strcmp(k, "merge.ff")) {
		int boolval = git_config_maybe_bool(k, v);
		if (0 <= boolval) {
			fast_forward = boolval ? FF_ALLOW : FF_NO;
		} else if (v && !strcmp(v, "only")) {
			fast_forward = FF_ONLY;
		} /* do not barf on values from future versions of git */
		return 0;
	} else if (!strcmp(k, "merge.defaulttoupstream")) {
		default_to_upstream = git_config_bool(k, v);
		return 0;
	} else if (!strcmp(k, "commit.gpgsign")) {
		sign_commit = git_config_bool(k, v) ? "" : NULL;
		return 0;
	}

	status = fmt_merge_msg_config(k, v, cb);
	if (status)
		return status;
	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;
	return git_diff_ui_config(k, v, cb);
}