static void prepare_symlink_changes(struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		if ((patch->old_name && S_ISLNK(patch->old_mode)) &&
		    (patch->is_rename || patch->is_delete))
			/* the symlink at patch->old_name is removed */
			register_symlink_changes(patch->old_name, SYMLINK_GOES_AWAY);

		if (patch->new_name && S_ISLNK(patch->new_mode))
			/* the symlink at patch->new_name is created or remains */
			register_symlink_changes(patch->new_name, SYMLINK_IN_RESULT);
	}
}