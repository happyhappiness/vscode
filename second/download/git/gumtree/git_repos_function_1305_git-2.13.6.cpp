static uintptr_t check_symlink_changes(struct apply_state *state, const char *path)
{
	struct string_list_item *ent;

	ent = string_list_lookup(&state->symlink_changes, path);
	if (!ent)
		return 0;
	return (uintptr_t)ent->util;
}