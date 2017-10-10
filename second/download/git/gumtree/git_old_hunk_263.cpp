	NULL
};
static int patch_interactive, add_interactive, edit_interactive;
static int take_worktree_changes;

struct update_callback_data {
	int flags, force_mode;
	int add_errors;
};

static int fix_unmerged_status(struct diff_filepair *p,
			       struct update_callback_data *data)
{
	if (p->status != DIFF_STATUS_UNMERGED)
		return p->status;
	if (!(data->flags & ADD_CACHE_IGNORE_REMOVAL) && !p->two->mode)
