		if (ret) {
			src = dst->buf;
			len = dst->len;
		}
	}

	ret_filter = apply_filter(path, src, len, -1, dst, ca.drv, CAP_SMUDGE);
	if (!ret_filter && ca.drv && ca.drv->required)
		die("%s: smudge filter %s failed", path, ca.drv->name);

	return ret | ret_filter;
}

int convert_to_working_tree(const char *path, const char *src, size_t len, struct strbuf *dst)
{
	return convert_to_working_tree_internal(path, src, len, dst, 0);
}

int renormalize_buffer(const struct index_state *istate, const char *path,
		       const char *src, size_t len, struct strbuf *dst)
{
	int ret = convert_to_working_tree_internal(path, src, len, dst, 1);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}
	return ret | convert_to_git(istate, path, src, len, dst, SAFE_CRLF_RENORMALIZE);
}
