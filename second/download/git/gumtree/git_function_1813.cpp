static void die_on_unsafe_path(struct patch *patch)
{
	const char *old_name = NULL;
	const char *new_name = NULL;
	if (patch->is_delete)
		old_name = patch->old_name;
	else if (!patch->is_new && !patch->is_copy)
		old_name = patch->old_name;
	if (!patch->is_delete)
		new_name = patch->new_name;

	if (old_name && !verify_path(old_name))
		die(_("invalid path '%s'"), old_name);
	if (new_name && !verify_path(new_name))
		die(_("invalid path '%s'"), new_name);
}