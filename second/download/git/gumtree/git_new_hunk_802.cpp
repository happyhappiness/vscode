	struct commit_name *name = commit->util;

	if (commit->object.parsed) {
		pp_commit_easy(CMIT_FMT_ONELINE, commit, &pretty);
		pretty_str = pretty.buf;
	}
	skip_prefix(pretty_str, "[PATCH] ", &pretty_str);

	if (!no_name) {
		if (name && name->head_name) {
			printf("[%s", name->head_name);
			if (name->generation) {
				if (name->generation == 1)
