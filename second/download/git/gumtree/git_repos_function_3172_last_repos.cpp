int renormalize_buffer(const struct index_state *istate, const char *path,
		       const char *src, size_t len, struct strbuf *dst)
{
	int ret = convert_to_working_tree_internal(path, src, len, dst, 1, NULL);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}
	return ret | convert_to_git(istate, path, src, len, dst, SAFE_CRLF_RENORMALIZE);
}