int convert_to_git(const char *path, const char *src, size_t len,
                   struct strbuf *dst, enum safe_crlf checksafe)
{
	int ret = 0;
	const char *filter = NULL;
	int required = 0;
	struct conv_attrs ca;

	convert_attrs(&ca, path);
	if (ca.drv) {
		filter = ca.drv->clean;
		required = ca.drv->required;
	}

	ret |= apply_filter(path, src, len, -1, dst, filter);
	if (!ret && required)
		die("%s: clean filter '%s' failed", path, ca.drv->name);

	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	ca.crlf_action = input_crlf_action(ca.crlf_action, ca.eol_attr);
	ret |= crlf_to_git(path, src, len, dst, ca.crlf_action, checksafe);
	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	return ret | ident_to_git(path, src, len, dst, ca.ident);
}