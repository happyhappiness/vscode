int renormalize_buffer(const char *path, const char *src, size_t len, struct strbuf *dst)
{
	int ret = convert_to_working_tree_internal(path, src, len, dst, 1);
	if (ret) {
		src = dst->buf;
		len = dst->len;
	}
	return ret | convert_to_git(path, src, len, dst, SAFE_CRLF_FALSE);
}