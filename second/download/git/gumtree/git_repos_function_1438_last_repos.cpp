static int apply_patch(struct apply_state *state,
		       int fd,
		       const char *filename,
		       int options)
{
	size_t offset;
	struct strbuf buf = STRBUF_INIT; /* owns the patch text */
	struct patch *list = NULL, **listp = &list;
	int skipped_patch = 0;
	int res = 0;

	state->patch_input_file = filename;
	if (read_patch_file(&buf, fd) < 0)
		return -128;
	offset = 0;
	while (offset < buf.len) {
		struct patch *patch;
		int nr;

		patch = xcalloc(1, sizeof(*patch));
		patch->inaccurate_eof = !!(options & APPLY_OPT_INACCURATE_EOF);
		patch->recount =  !!(options & APPLY_OPT_RECOUNT);
		nr = parse_chunk(state, buf.buf + offset, buf.len - offset, patch);
		if (nr < 0) {
			free_patch(patch);
			if (nr == -128) {
				res = -128;
				goto end;
			}
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
			if (state->apply_verbosity > verbosity_normal)
				say_patch_name(stderr, _("Skipped patch '%s'."), patch);
			free_patch(patch);
			skipped_patch++;
		}
		offset += nr;
	}

	if (!list && !skipped_patch) {
		error(_("unrecognized input"));
		res = -128;
		goto end;
	}

	if (state->whitespace_error && (state->ws_error_action == die_on_ws_error))
		state->apply = 0;

	state->update_index = state->check_index && state->apply;
	if (state->update_index && state->newfd < 0) {
		if (state->index_file)
			state->newfd = hold_lock_file_for_update(state->lock_file,
								 state->index_file,
								 LOCK_DIE_ON_ERROR);
		else
			state->newfd = hold_locked_index(state->lock_file, LOCK_DIE_ON_ERROR);
	}

	if (state->check_index && read_apply_cache(state) < 0) {
		error(_("unable to read index file"));
		res = -128;
		goto end;
	}

	if (state->check || state->apply) {
		int r = check_patch_list(state, list);
		if (r == -128) {
			res = -128;
			goto end;
		}
		if (r < 0 && !state->apply_with_reject) {
			res = -1;
			goto end;
		}
	}

	if (state->apply) {
		int write_res = write_out_results(state, list);
		if (write_res < 0) {
			res = -128;
			goto end;
		}
		if (write_res > 0) {
			/* with --3way, we still need to write the index out */
			res = state->apply_with_reject ? -1 : 1;
			goto end;
		}
	}

	if (state->fake_ancestor &&
	    build_fake_ancestor(state, list)) {
		res = -128;
		goto end;
	}

	if (state->diffstat && state->apply_verbosity > verbosity_silent)
		stat_patch_list(state, list);

	if (state->numstat && state->apply_verbosity > verbosity_silent)
		numstat_patch_list(state, list);

	if (state->summary && state->apply_verbosity > verbosity_silent)
		summary_patch_list(list);

end:
	free_patch_list(list);
	strbuf_release(&buf);
	string_list_clear(&state->fn_table, 0);
	return res;
}