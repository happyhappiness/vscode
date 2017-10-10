	else {
		printf("%s ", find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV));
		if (parse_commit(commit) != 0)
			printf(_("(bad commit)\n"));
		else {
			const char *title;
			const char *msg = get_commit_buffer(commit, NULL);
			int len = find_commit_subject(msg, &title);
			if (len)
				printf("%.*s\n", len, title);
			unuse_commit_buffer(commit, msg);
		}
	}
}

static int add_cacheinfo(unsigned int mode, const unsigned char *sha1,
		const char *path, int stage, int refresh, int options)
