		strbuf_addch(&sb, '\n');
		fprintf(f, "%s", sb.buf);
	}
	strbuf_release(&sb);
}

void show_submodule_summary(FILE *f, const char *path,
		const char *line_prefix,
		unsigned char one[20], unsigned char two[20],
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset)
{
	struct rev_info rev;
	struct commit *left = NULL, *right = NULL;
	const char *message = NULL;
	struct strbuf sb = STRBUF_INIT;
	int fast_forward = 0, fast_backward = 0;

	if (is_null_sha1(two))
		message = "(submodule deleted)";
	else if (add_submodule_odb(path))
		message = "(not checked out)";
	else if (is_null_sha1(one))
		message = "(new submodule)";
	else if (!(left = lookup_commit_reference(one)) ||
		 !(right = lookup_commit_reference(two)))
		message = "(commits not present)";
	else if (prepare_submodule_summary(&rev, path, left, right,
					   &fast_forward, &fast_backward))
		message = "(revision walker failed)";

	if (dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
		fprintf(f, "%sSubmodule %s contains untracked content\n",
			line_prefix, path);
	if (dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
		fprintf(f, "%sSubmodule %s contains modified content\n",
			line_prefix, path);

	if (!hashcmp(one, two)) {
		strbuf_release(&sb);
		return;
	}

	strbuf_addf(&sb, "%s%sSubmodule %s ", line_prefix, meta, path);
	strbuf_add_unique_abbrev(&sb, one, DEFAULT_ABBREV);
	strbuf_addstr(&sb, (fast_backward || fast_forward) ? ".." : "...");
	strbuf_add_unique_abbrev(&sb, two, DEFAULT_ABBREV);
	if (message)
		strbuf_addf(&sb, " %s%s\n", message, reset);
	else
		strbuf_addf(&sb, "%s:%s\n", fast_backward ? " (rewind)" : "", reset);
	fwrite(sb.buf, sb.len, 1, f);

	if (!message) /* only NULL if we succeeded in setting up the walk */
		print_submodule_summary(&rev, f, line_prefix, del, add, reset);
	if (left)
		clear_commit_marks(left, ~0);
	if (right)
		clear_commit_marks(right, ~0);

	strbuf_release(&sb);
}

void set_config_fetch_recurse_submodules(int value)
{
	config_fetch_recurse_submodules = value;
}
