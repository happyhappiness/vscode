static void prepare_symlink_changes(struct apply_state *state, struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		if ((patch->old_name && S_ISLNK(patch->old_mode)) &&
		    (patch->is_rename || patch->is_delete))
			/* the symlink at patch->old_name is removed */
			register_symlink_changes(state, patch->old_name, APPLY_SYMLINK_GOES_AWAY);

		if (patch->new_name && S_ISLNK(patch->new_mode))
			/* the symlink at patch->new_name is created or remains */
			register_symlink_changes(state, patch->new_name, APPLY_SYMLINK_IN_RESULT);
	}
}