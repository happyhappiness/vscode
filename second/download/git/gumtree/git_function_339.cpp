static int apply_patch(struct apply_state *state,
		       int fd,
		       const char *filename,
		       int options)
{
	size_t offset;
	struct strbuf buf = STRBUF_INIT; /* owns the patch text */
	struct patch *list = NULL, **listp = &list;
	int skipped_patch = 0;

	state->patch_input_file = filename;
	read_patch_file(&buf, fd);
	offset = 0;
	while (offset < buf.len) {
		struct patch *patch;
		int nr;

		patch = xcalloc(1, sizeof(*patch));
		patch->inaccurate_eof = !!(options & INACCURATE_EOF);
		patch->recount =  !!(options & RECOUNT);
		nr = parse_chunk(state, buf.buf + offset, buf.len - offset, patch);
		if (nr < 0) {
			free_patch(patch);
			break;
		}
		if (state->apply_in_reverse)
			reverse_patches(patch);
		if (use_patch(state, patch)) {
			patch_stats(state, patch);
			*listp = patch;
			listp = &patch->next;
		}
		else {
			if (state->apply_verbosely)
				say_patch_name(stderr, _("Skipped patch '%s'."), patch);
			free_patch(patch);
			skipped_patch++;
		}
		offset += nr;
	}

	if (!list && !skipped_patch)
		die(_("unrecognized input"));

	if (state->whitespace_error && (state->ws_error_action == die_on_ws_error))
		state->apply = 0;

	state->update_index = state->check_index && state->apply;
	if (state->update_index && state->newfd < 0)
		state->newfd = hold_locked_index(state->lock_file, 1);

	if (state->check_index) {
		if (read_cache() < 0)
			die(_("unable to read index file"));
	}

	if ((state->check || state->apply) &&
	    check_patch_list(state, list) < 0 &&
	    !state->apply_with_reject)
		exit(1);

	if (state->apply && write_out_results(state, list)) {
		if (state->apply_with_reject)
			exit(1);
		/* with --3way, we still need to write the index out */
		return 1;
	}

	if (state->fake_ancestor)
		build_fake_ancestor(list, state->fake_ancestor);

	if (state->diffstat)
		stat_patch_list(state, list);

	if (state->numstat)
		numstat_patch_list(state, list);

	if (state->summary)
		summary_patch_list(list);

	free_patch_list(list);
	strbuf_release(&buf);
	string_list_clear(&state->fn_table, 0);
	return 0;
}