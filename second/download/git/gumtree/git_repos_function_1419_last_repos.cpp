static int get_current_oid(struct apply_state *state, const char *path,
			   struct object_id *oid)
{
	int pos;

	if (read_apply_cache(state) < 0)
		return -1;
	pos = cache_name_pos(path, strlen(path));
	if (pos < 0)
		return -1;
	oidcpy(oid, &active_cache[pos]->oid);
	return 0;
}