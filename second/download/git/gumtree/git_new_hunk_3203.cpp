		die("%s: clean filter '%s' failed", path, ca.drv->name);

	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	ret |= crlf_to_git(path, src, len, dst, ca.crlf_action, checksafe);
	if (ret && dst) {
		src = dst->buf;
		len = dst->len;
	}
	return ret | ident_to_git(path, src, len, dst, ca.ident);
