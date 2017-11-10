static uintptr_t check_symlink_changes(const char *path)
{
	struct string_list_item *ent;

	ent = string_list_lookup(&symlink_changes, path);
	if (!ent)
		return 0;
	return (uintptr_t)ent->util;
}