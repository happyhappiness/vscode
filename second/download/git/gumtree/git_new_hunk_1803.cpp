		if (ret) {
			src = dst->buf;
			len = dst->len;
		}
	}

	ret_filter = apply_filter(path, src, len, -1, dst, filter);
	if (!ret_filter && required)
		die("%s: smudge filter %s failed", path, ca.drv->name);

	return ret | ret_filter;
}

