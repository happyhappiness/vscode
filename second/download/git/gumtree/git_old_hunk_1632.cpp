{
	int ret = 0;
	struct conv_attrs ca;

	convert_attrs(&ca, path);

	ret |= apply_filter(path, src, len, -1, dst, ca.drv, CAP_CLEAN);
	if (!ret && ca.drv && ca.drv->required)
		die("%s: clean filter '%s' failed", path, ca.drv->name);

	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	ret |= crlf_to_git(istate, path, src, len, dst, ca.crlf_action, checksafe);
	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	return ret | ident_to_git(path, src, len, dst, ca.ident);
}

void convert_to_git_filter_fd(const struct index_state *istate,
			      const char *path, int fd, struct strbuf *dst,
