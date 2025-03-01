
	item = string_list_lookup(&info->complete_reflogs, branch);
	if (item)
		reflogs = item->util;
	else {
		if (*branch == '\0') {
			struct object_id oid;
			free(branch);
			branch = resolve_refdup("HEAD", 0, oid.hash, NULL);
			if (!branch)
				die ("No current branch");

		}
		reflogs = read_complete_reflog(branch);
		if (!reflogs || reflogs->nr == 0) {
			struct object_id oid;
			char *b;
			if (dwim_log(branch, strlen(branch), oid.hash, &b) == 1) {
				if (reflogs) {
					free(reflogs->ref);
					free(reflogs);
				}
				free(branch);
				branch = b;
