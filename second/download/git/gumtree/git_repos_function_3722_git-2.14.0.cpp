static void show_submodule_header(FILE *f, const char *path,
		const char *line_prefix,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule, const char *meta,
		const char *reset,
		struct commit **left, struct commit **right,
		struct commit_list **merge_bases)
{
	const char *message = NULL;
	struct strbuf sb = STRBUF_INIT;
	int fast_forward = 0, fast_backward = 0;

	if (dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
		fprintf(f, "%sSubmodule %s contains untracked content\n",
			line_prefix, path);
	if (dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
		fprintf(f, "%sSubmodule %s contains modified content\n",
			line_prefix, path);

	if (is_null_oid(one))
		message = "(new submodule)";
	else if (is_null_oid(two))
		message = "(submodule deleted)";

	if (add_submodule_odb(path)) {
		if (!message)
			message = "(not initialized)";
		goto output_header;
	}

	/*
	 * Attempt to lookup the commit references, and determine if this is
	 * a fast forward or fast backwards update.
	 */
	*left = lookup_commit_reference(one);
	*right = lookup_commit_reference(two);

	/*
	 * Warn about missing commits in the submodule project, but only if
	 * they aren't null.
	 */
	if ((!is_null_oid(one) && !*left) ||
	     (!is_null_oid(two) && !*right))
		message = "(commits not present)";

	*merge_bases = get_merge_bases(*left, *right);
	if (*merge_bases) {
		if ((*merge_bases)->item == *left)
			fast_forward = 1;
		else if ((*merge_bases)->item == *right)
			fast_backward = 1;
	}

	if (!oidcmp(one, two)) {
		strbuf_release(&sb);
		return;
	}

output_header:
	strbuf_addf(&sb, "%s%sSubmodule %s ", line_prefix, meta, path);
	strbuf_add_unique_abbrev(&sb, one->hash, DEFAULT_ABBREV);
	strbuf_addstr(&sb, (fast_backward || fast_forward) ? ".." : "...");
	strbuf_add_unique_abbrev(&sb, two->hash, DEFAULT_ABBREV);
	if (message)
		strbuf_addf(&sb, " %s%s\n", message, reset);
	else
		strbuf_addf(&sb, "%s:%s\n", fast_backward ? " (rewind)" : "", reset);
	fwrite(sb.buf, sb.len, 1, f);

	strbuf_release(&sb);
}