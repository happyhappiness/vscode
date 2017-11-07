int read_branch_desc(struct strbuf *buf, const char *branch_name)
{
	struct branch_desc_cb cb;
	struct strbuf name = STRBUF_INIT;
	strbuf_addf(&name, "branch.%s.description", branch_name);
	cb.config_name = name.buf;
	cb.value = NULL;
	if (git_config(read_branch_desc_cb, &cb) < 0) {
		strbuf_release(&name);
		return -1;
	}
	if (cb.value)
		strbuf_addstr(buf, cb.value);
	strbuf_release(&name);
	return 0;
}