	if (item)
		reflogs = item->util;
	else {
		if (*branch == '\0') {
			unsigned char sha1[20];
			free(branch);
			branch = resolve_refdup("HEAD", sha1, 0, NULL);
			if (!branch)
				die ("No current branch");

		}
		reflogs = read_complete_reflog(branch);
		if (!reflogs || reflogs->nr == 0) {
