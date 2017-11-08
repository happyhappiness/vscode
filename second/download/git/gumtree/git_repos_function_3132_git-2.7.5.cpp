static int blob_unchanged(const unsigned char *o_sha,
			  unsigned o_mode,
			  const unsigned char *a_sha,
			  unsigned a_mode,
			  int renormalize, const char *path)
{
	struct strbuf o = STRBUF_INIT;
	struct strbuf a = STRBUF_INIT;
	int ret = 0; /* assume changed for safety */

	if (a_mode != o_mode)
		return 0;
	if (sha_eq(o_sha, a_sha))
		return 1;
	if (!renormalize)
		return 0;

	assert(o_sha && a_sha);
	if (read_sha1_strbuf(o_sha, &o) || read_sha1_strbuf(a_sha, &a))
		goto error_return;
	/*
	 * Note: binary | is used so that both renormalizations are
	 * performed.  Comparison can be skipped if both files are
	 * unchanged since their sha1s have already been compared.
	 */
	if (renormalize_buffer(path, o.buf, o.len, &o) |
	    renormalize_buffer(path, a.buf, a.len, &a))
		ret = (o.len == a.len && !memcmp(o.buf, a.buf, o.len));

error_return:
	strbuf_release(&o);
	strbuf_release(&a);
	return ret;
}