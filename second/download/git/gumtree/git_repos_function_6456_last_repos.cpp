static const char *original_update_refname(struct ref_update *update)
{
	while (update->parent_update)
		update = update->parent_update;

	return update->refname;
}