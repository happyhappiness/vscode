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
