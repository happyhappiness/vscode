void show_submodule_inline_diff(FILE *f, const char *path,
		const char *line_prefix,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule, const char *meta,
		const char *del, const char *add, const char *reset,
		const struct diff_options *o)
{
	const struct object_id *old = &empty_tree_oid, *new = &empty_tree_oid;
	struct commit *left = NULL, *right = NULL;
	struct commit_list *merge_bases = NULL;
	struct strbuf submodule_dir = STRBUF_INIT;
	struct child_process cp = CHILD_PROCESS_INIT;

	show_submodule_header(f, path, line_prefix, one, two, dirty_submodule,
			      meta, reset, &left, &right, &merge_bases);

	/* We need a valid left and right commit to display a difference */
	if (!(left || is_null_oid(one)) ||
	    !(right || is_null_oid(two)))
		goto done;

	if (left)
		old = one;
	if (right)
		new = two;

	fflush(f);
	cp.git_cmd = 1;
	cp.dir = path;
	cp.out = dup(fileno(f));
	cp.no_stdin = 1;

	/* TODO: other options may need to be passed here. */
	argv_array_push(&cp.args, "diff");
	argv_array_pushf(&cp.args, "--line-prefix=%s", line_prefix);
	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
		argv_array_pushf(&cp.args, "--src-prefix=%s%s/",
				 o->b_prefix, path);
		argv_array_pushf(&cp.args, "--dst-prefix=%s%s/",
				 o->a_prefix, path);
	} else {
		argv_array_pushf(&cp.args, "--src-prefix=%s%s/",
				 o->a_prefix, path);
		argv_array_pushf(&cp.args, "--dst-prefix=%s%s/",
				 o->b_prefix, path);
	}
	argv_array_push(&cp.args, oid_to_hex(old));
	/*
	 * If the submodule has modified content, we will diff against the
	 * work tree, under the assumption that the user has asked for the
	 * diff format and wishes to actually see all differences even if they
	 * haven't yet been committed to the submodule yet.
	 */
	if (!(dirty_submodule & DIRTY_SUBMODULE_MODIFIED))
		argv_array_push(&cp.args, oid_to_hex(new));

	if (run_command(&cp))
		fprintf(f, "(diff failed)\n");

done:
	strbuf_release(&submodule_dir);
	if (merge_bases)
		free_commit_list(merge_bases);
	if (left)
		clear_commit_marks(left, ~0);
	if (right)
		clear_commit_marks(right, ~0);
}