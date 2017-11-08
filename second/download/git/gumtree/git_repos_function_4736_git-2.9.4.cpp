static uintptr_t register_symlink_changes(const char *path, uintptr_t what)
{
	struct string_list_item *ent;

	ent = string_list_lookup(&symlink_changes, path);
	if (!ent) {
		ent = string_list_insert(&symlink_changes, path);
		ent->util = (void *)0;
	}
	ent->util = (void *)(what | ((uintptr_t)ent->util));
	return (uintptr_t)ent->util;
}