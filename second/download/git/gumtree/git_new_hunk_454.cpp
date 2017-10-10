}

int convert_to_git(const char *path, const char *src, size_t len,
                   struct strbuf *dst, enum safe_crlf checksafe)
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
