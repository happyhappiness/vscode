static void resolve(const struct traverse_info *info, struct name_entry *ours, struct name_entry *result)
{
	struct merge_list *orig, *final;
	const char *path;

	/* If it's already ours, don't bother showing it */
	if (!ours)
		return;

	path = traverse_path(info, result);
	orig = create_entry(2, ours->mode, ours->oid, path);
	final = create_entry(0, result->mode, result->oid, path);

	final->link = orig;

	add_merge_entry(final);
}