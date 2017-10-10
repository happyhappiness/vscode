
	item = string_list_lookup(&info->complete_reflogs, branch);
	if (item)
		reflogs = item->util;
	else {
		if (*branch == '\0') {
			unsigned char sha1[20];
			free(branch);
			branch = resolve_refdup("HEAD", 0, sha1, NULL);
			if (!branch)
				die ("No current branch");

		}
		reflogs = read_complete_reflog(branch);
		if (!reflogs || reflogs->nr == 0) {
			unsigned char sha1[20];
			char *b;
			if (dwim_log(branch, strlen(branch), sha1, &b) == 1) {
				if (reflogs) {
					free(reflogs->ref);
					free(reflogs);
				}
				free(branch);
				branch = b;
