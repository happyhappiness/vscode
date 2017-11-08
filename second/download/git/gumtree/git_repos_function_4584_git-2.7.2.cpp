static int parse_git_header(const char *line, int len, unsigned int size, struct patch *patch)
{
	unsigned long offset;

	/* A git diff has explicit new/delete information, so we don't guess */
	patch->is_new = 0;
	patch->is_delete = 0;

	/*
	 * Some things may not have the old name in the
	 * rest of the headers anywhere (pure mode changes,
	 * or removing or adding empty files), so we get
	 * the default name from the header.
	 */
	patch->def_name = git_header_name(line, len);
	if (patch->def_name && root.len) {
		char *s = xstrfmt("%s%s", root.buf, patch->def_name);
		free(patch->def_name);
		patch->def_name = s;
	}

	line += len;
	size -= len;
	linenr++;
	for (offset = len ; size > 0 ; offset += len, size -= len, line += len, linenr++) {
		static const struct opentry {
			const char *str;
			int (*fn)(const char *, struct patch *);
		} optable[] = {
			{ "@@ -", gitdiff_hdrend },
			{ "--- ", gitdiff_oldname },
			{ "+++ ", gitdiff_newname },
			{ "old mode ", gitdiff_oldmode },
			{ "new mode ", gitdiff_newmode },
			{ "deleted file mode ", gitdiff_delete },
			{ "new file mode ", gitdiff_newfile },
			{ "copy from ", gitdiff_copysrc },
			{ "copy to ", gitdiff_copydst },
			{ "rename old ", gitdiff_renamesrc },
			{ "rename new ", gitdiff_renamedst },
			{ "rename from ", gitdiff_renamesrc },
			{ "rename to ", gitdiff_renamedst },
			{ "similarity index ", gitdiff_similarity },
			{ "dissimilarity index ", gitdiff_dissimilarity },
			{ "index ", gitdiff_index },
			{ "", gitdiff_unrecognized },
		};
		int i;

		len = linelen(line, size);
		if (!len || line[len-1] != '\n')
			break;
		for (i = 0; i < ARRAY_SIZE(optable); i++) {
			const struct opentry *p = optable + i;
			int oplen = strlen(p->str);
			if (len < oplen || memcmp(p->str, line, oplen))
				continue;
			if (p->fn(line + oplen, patch) < 0)
				return offset;
			break;
		}
	}

	return offset;
}