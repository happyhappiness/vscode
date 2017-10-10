
static struct lock_file lock_file;

#define INACCURATE_EOF	(1<<0)
#define RECOUNT		(1<<1)

static int apply_patch(int fd, const char *filename, int options)
{
	size_t offset;
	struct strbuf buf = STRBUF_INIT; /* owns the patch text */
	struct patch *list = NULL, **listp = &list;
	int skipped_patch = 0;

	patch_input_file = filename;
	read_patch_file(&buf, fd);
	offset = 0;
	while (offset < buf.len) {
		struct patch *patch;
		int nr;

		patch = xcalloc(1, sizeof(*patch));
		patch->inaccurate_eof = !!(options & INACCURATE_EOF);
		patch->recount =  !!(options & RECOUNT);
		nr = parse_chunk(buf.buf + offset, buf.len - offset, patch);
		if (nr < 0) {
			free_patch(patch);
			break;
		}
		if (apply_in_reverse)
			reverse_patches(patch);
		if (use_patch(patch)) {
			patch_stats(patch);
			*listp = patch;
			listp = &patch->next;
		}
		else {
			if (apply_verbosely)
				say_patch_name(stderr, _("Skipped patch '%s'."), patch);
			free_patch(patch);
			skipped_patch++;
		}
		offset += nr;
	}

	if (!list && !skipped_patch)
		die(_("unrecognized input"));

	if (whitespace_error && (ws_error_action == die_on_ws_error))
		apply = 0;

	update_index = check_index && apply;
	if (update_index && newfd < 0)
		newfd = hold_locked_index(&lock_file, 1);

	if (check_index) {
		if (read_cache() < 0)
			die(_("unable to read index file"));
	}

	if ((check || apply) &&
	    check_patch_list(list) < 0 &&
	    !apply_with_reject)
		exit(1);

	if (apply && write_out_results(list)) {
		if (apply_with_reject)
			exit(1);
		/* with --3way, we still need to write the index out */
		return 1;
	}

	if (fake_ancestor)
		build_fake_ancestor(list, fake_ancestor);

	if (diffstat)
		stat_patch_list(list);

	if (numstat)
		numstat_patch_list(list);

	if (summary)
		summary_patch_list(list);

	free_patch_list(list);
	strbuf_release(&buf);
	string_list_clear(&fn_table, 0);
	return 0;
}

static void git_apply_config(void)
{
	git_config_get_string_const("apply.whitespace", &apply_default_whitespace);
