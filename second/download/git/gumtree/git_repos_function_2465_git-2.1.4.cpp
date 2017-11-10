int head_ref_namespaced(each_ref_fn fn, void *cb_data)
{
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;
	unsigned char sha1[20];
	int flag;

	strbuf_addf(&buf, "%sHEAD", get_git_namespace());
	if (!read_ref_full(buf.buf, sha1, 1, &flag))
		ret = fn(buf.buf, sha1, flag, cb_data);
	strbuf_release(&buf);

	return ret;
}