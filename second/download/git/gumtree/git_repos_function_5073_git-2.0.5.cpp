static int show_tree(const unsigned char *sha1, const char *base, int baselen,
		const char *pathname, unsigned mode, int stage, void *context)
{
	int retval = 0;
	const char *type = blob_type;

	if (S_ISGITLINK(mode)) {
		/*
		 * Maybe we want to have some recursive version here?
		 *
		 * Something similar to this incomplete example:
		 *
		if (show_subprojects(base, baselen, pathname))
			retval = READ_TREE_RECURSIVE;
		 *
		 */
		type = commit_type;
	} else if (S_ISDIR(mode)) {
		if (show_recursive(base, baselen, pathname)) {
			retval = READ_TREE_RECURSIVE;
			if (!(ls_options & LS_SHOW_TREES))
				return retval;
		}
		type = tree_type;
	}
	else if (ls_options & LS_TREE_ONLY)
		return 0;

	if (chomp_prefix &&
	    (baselen < chomp_prefix || memcmp(ls_tree_prefix, base, chomp_prefix)))
		return 0;

	if (!(ls_options & LS_NAME_ONLY)) {
		if (ls_options & LS_SHOW_SIZE) {
			char size_text[24];
			if (!strcmp(type, blob_type)) {
				unsigned long size;
				if (sha1_object_info(sha1, &size) == OBJ_BAD)
					strcpy(size_text, "BAD");
				else
					snprintf(size_text, sizeof(size_text),
						 "%lu", size);
			} else
				strcpy(size_text, "-");
			printf("%06o %s %s %7s\t", mode, type,
			       find_unique_abbrev(sha1, abbrev),
			       size_text);
		} else
			printf("%06o %s %s\t", mode, type,
			       find_unique_abbrev(sha1, abbrev));
	}
	write_name_quotedpfx(base + chomp_prefix, baselen - chomp_prefix,
			  pathname, stdout, line_termination);
	return retval;
}