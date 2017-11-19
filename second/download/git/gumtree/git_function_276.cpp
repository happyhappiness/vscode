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
	} else if (name) {
		if (S_ISGITLINK(expected_mode)) {
			if (ce)
				return read_file_or_gitlink(ce, buf);
			else
				return SUBMODULE_PATCH_WITHOUT_INDEX;
		} else if (has_symlink_leading_path(name, strlen(name))) {
			return error(_("reading from '%s' beyond a symbolic link"), name);
		} else {
			if (read_old_data(st, name, buf))
				return error(_("failed to read %s"), name);
		}
	}
	return 0;
}