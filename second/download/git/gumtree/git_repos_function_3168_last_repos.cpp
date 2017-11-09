void convert_to_git_filter_fd(const struct index_state *istate,
			      const char *path, int fd, struct strbuf *dst,
			      enum safe_crlf checksafe)
{
	struct conv_attrs ca;
	convert_attrs(&ca, path);

	assert(ca.drv);
	assert(ca.drv->clean || ca.drv->process);

	if (!apply_filter(path, NULL, 0, fd, dst, ca.drv, CAP_CLEAN, NULL))
		die("%s: clean filter '%s' failed", path, ca.drv->name);

	crlf_to_git(istate, path, dst->buf, dst->len, dst, ca.crlf_action, checksafe);
	ident_to_git(path, dst->buf, dst->len, dst, ca.ident);
}