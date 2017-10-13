static int load_current(struct apply_state *state,
			struct image *image,
			struct patch *patch)
{
	struct strbuf buf = STRBUF_INIT;
	int status, pos;
	size_t len;
	char *img;
	struct stat st;
	struct cache_entry *ce;
	char *name = patch->new_name;
	unsigned mode = patch->new_mode;

	if (!patch->is_new)
		die("BUG: patch to %s is not a creation", patch->old_name);

	pos = cache_name_pos(name, strlen(name));
	if (pos < 0)
		return error(_("%s: does not exist in index"), name);
	ce = active_cache[pos];
	if (lstat(name, &st)) {
		if (errno != ENOENT)
			return error(_("%s: %s"), name, strerror(errno));
		if (checkout_target(&the_index, ce, &st))
			return -1;
	}
	if (verify_index_match(ce, &st))
		return error(_("%s: does not match index"), name);

	status = load_patch_target(state, &buf, ce, &st, name, mode);
	if (status < 0)
		return status;
	else if (status)
		return -1;
	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
	return 0;
}