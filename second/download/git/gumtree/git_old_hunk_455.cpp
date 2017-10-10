			      enum safe_crlf checksafe)
{
	struct conv_attrs ca;
	convert_attrs(&ca, path);

	assert(ca.drv);
	assert(ca.drv->clean);

	if (!apply_filter(path, NULL, 0, fd, dst, ca.drv->clean))
		die("%s: clean filter '%s' failed", path, ca.drv->name);

	crlf_to_git(path, dst->buf, dst->len, dst, ca.crlf_action, checksafe);
	ident_to_git(path, dst->buf, dst->len, dst, ca.ident);
}

static int convert_to_working_tree_internal(const char *path, const char *src,
					    size_t len, struct strbuf *dst,
					    int normalizing)
{
	int ret = 0, ret_filter = 0;
	const char *filter = NULL;
	int required = 0;
	struct conv_attrs ca;

	convert_attrs(&ca, path);
	if (ca.drv) {
		filter = ca.drv->smudge;
		required = ca.drv->required;
	}

	ret |= ident_to_worktree(path, src, len, dst, ca.ident);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}
	/*
	 * CRLF conversion can be skipped if normalizing, unless there
	 * is a smudge filter.  The filter might expect CRLFs.
	 */
	if (filter || !normalizing) {
		ret |= crlf_to_worktree(path, src, len, dst, ca.crlf_action);
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

int convert_to_working_tree(const char *path, const char *src, size_t len, struct strbuf *dst)
