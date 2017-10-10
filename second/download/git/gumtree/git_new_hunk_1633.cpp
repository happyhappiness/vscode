	struct conv_attrs ca;
	convert_attrs(&ca, path);

	assert(ca.drv);
	assert(ca.drv->clean || ca.drv->process);

	if (!apply_filter(path, NULL, 0, fd, dst, ca.drv, CAP_CLEAN, NULL))
		die("%s: clean filter '%s' failed", path, ca.drv->name);

	crlf_to_git(istate, path, dst->buf, dst->len, dst, ca.crlf_action, checksafe);
	ident_to_git(path, dst->buf, dst->len, dst, ca.ident);
}

static int convert_to_working_tree_internal(const char *path, const char *src,
					    size_t len, struct strbuf *dst,
					    int normalizing, struct delayed_checkout *dco)
{
	int ret = 0, ret_filter = 0;
	struct conv_attrs ca;

	convert_attrs(&ca, path);

