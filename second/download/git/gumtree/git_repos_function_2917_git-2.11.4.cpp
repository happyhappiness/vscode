static int convert_to_working_tree_internal(const char *path, const char *src,
					    size_t len, struct strbuf *dst,
					    int normalizing)
{
	int ret = 0, ret_filter = 0;
	struct conv_attrs ca;

	convert_attrs(&ca, path);

	ret |= ident_to_worktree(path, src, len, dst, ca.ident);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}
	/*
	 * CRLF conversion can be skipped if normalizing, unless there
	 * is a smudge or process filter (even if the process filter doesn't
	 * support smudge).  The filters might expect CRLFs.
	 */
	if ((ca.drv && (ca.drv->smudge || ca.drv->process)) || !normalizing) {
		ret |= crlf_to_worktree(path, src, len, dst, ca.crlf_action);
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