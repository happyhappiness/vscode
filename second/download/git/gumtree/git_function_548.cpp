static void wt_porcelain_v2_print_tracking(struct wt_status *s)
{
	struct branch *branch;
	const char *base;
	const char *branch_name;
	struct wt_status_state state;
	int ab_info, nr_ahead, nr_behind;
	char eol = s->null_termination ? '\0' : '\n';

	memset(&state, 0, sizeof(state));
	wt_status_get_state(&state, s->branch && !strcmp(s->branch, "HEAD"));

	fprintf(s->fp, "# branch.oid %s%c",
			(s->is_initial ? "(initial)" : sha1_to_hex(s->sha1_commit)),
			eol);

	if (!s->branch)
		fprintf(s->fp, "# branch.head %s%c", "(unknown)", eol);
	else {
		if (!strcmp(s->branch, "HEAD")) {
			fprintf(s->fp, "# branch.head %s%c", "(detached)", eol);

			if (state.rebase_in_progress || state.rebase_interactive_in_progress)
				branch_name = state.onto;
			else if (state.detached_from)
				branch_name = state.detached_from;
			else
				branch_name = "";
		} else {
			branch_name = NULL;
			skip_prefix(s->branch, "refs/heads/", &branch_name);

			fprintf(s->fp, "# branch.head %s%c", branch_name, eol);
		}

		/* Lookup stats on the upstream tracking branch, if set. */
		branch = branch_get(branch_name);
		base = NULL;
		ab_info = (stat_tracking_info(branch, &nr_ahead, &nr_behind, &base) == 0);
		if (base) {
			base = shorten_unambiguous_ref(base, 0);
			fprintf(s->fp, "# branch.upstream %s%c", base, eol);
			free((char *)base);

			if (ab_info)
				fprintf(s->fp, "# branch.ab +%d -%d%c", nr_ahead, nr_behind, eol);
		}
	}

	free(state.branch);
	free(state.onto);
	free(state.detached_from);
}