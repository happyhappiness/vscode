int convert_to_git(const struct index_state *istate,
		   const char *path, const char *src, size_t len,
                   struct strbuf *dst, enum safe_crlf checksafe)
{
	int ret = 0;
	struct conv_attrs ca;

	convert_attrs(&ca, path);

	ret |= apply_filter(path, src, len, -1, dst, ca.drv, CAP_CLEAN, NULL);
	if (!ret && ca.drv && ca.drv->required)
		die("%s: clean filter '%s' failed", path, ca.drv->name);

	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	if (checksafe != SAFE_CRLF_KEEP_CRLF) {
		ret |= crlf_to_git(istate, path, src, len, dst, ca.crlf_action, checksafe);
		if (ret && dst) {
			src = dst->buf;
			len = dst->len;
		}
	}
	return ret | ident_to_git(path, src, len, dst, ca.ident);
}