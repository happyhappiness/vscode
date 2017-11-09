static int create_file(struct apply_state *state, struct patch *patch)
{
	char *path = patch->new_name;
	unsigned mode = patch->new_mode;
	unsigned long size = patch->resultsize;
	char *buf = patch->result;

	if (!mode)
		mode = S_IFREG | 0644;
	if (create_one_file(state, path, mode, buf, size))
		return -1;

	if (patch->conflicted_threeway)
		return add_conflicted_stages_file(state, patch);
	else
		return add_index_file(state, path, mode, buf, size);
}