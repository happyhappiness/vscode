static int path_is_beyond_symlink(struct apply_state *state, const char *name_)
{
	int ret;
	struct strbuf name = STRBUF_INIT;

	assert(*name_ != '\0');
	strbuf_addstr(&name, name_);
	ret = path_is_beyond_symlink_1(state, &name);
	strbuf_release(&name);

	return ret;
}