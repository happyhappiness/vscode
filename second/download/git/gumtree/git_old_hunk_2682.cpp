	free(orig_head);
	free(rebase_amend);
	free(rebase_orig_head);
	return split_in_progress;
}

static void show_rebase_in_progress(struct wt_status *s,
				struct wt_status_state *state,
				const char *color)
{
	struct stat st;

	if (has_unmerged(s)) {
		if (state->branch)
			status_printf_ln(s, color,
					 _("You are currently rebasing branch '%s' on '%s'."),
					 state->branch,
					 state->onto);
		else
			status_printf_ln(s, color,
					 _("You are currently rebasing."));
		if (s->hints) {
			status_printf_ln(s, color,
				_("  (fix conflicts and then run \"git rebase --continue\")"));
			status_printf_ln(s, color,
				_("  (use \"git rebase --skip\" to skip this patch)"));
			status_printf_ln(s, color,
				_("  (use \"git rebase --abort\" to check out the original branch)"));
		}
	} else if (state->rebase_in_progress || !stat(git_path("MERGE_MSG"), &st)) {
		if (state->branch)
			status_printf_ln(s, color,
					 _("You are currently rebasing branch '%s' on '%s'."),
					 state->branch,
					 state->onto);
		else
			status_printf_ln(s, color,
					 _("You are currently rebasing."));
		if (s->hints)
			status_printf_ln(s, color,
				_("  (all conflicts fixed: run \"git rebase --continue\")"));
	} else if (split_commit_in_progress(s)) {
		if (state->branch)
			status_printf_ln(s, color,
