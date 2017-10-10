#define SUBMODULE_PATCH_WITHOUT_INDEX 1

static int load_patch_target(struct apply_state *state,
			     struct strbuf *buf,
			     const struct cache_entry *ce,
			     struct stat *st,
			     const char *name,
			     unsigned expected_mode)
{
	if (state->cached || state->check_index) {
		if (read_file_or_gitlink(ce, buf))
			return error(_("failed to read %s"), name);
