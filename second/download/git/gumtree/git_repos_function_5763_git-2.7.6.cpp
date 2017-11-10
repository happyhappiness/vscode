int safe_create_reflog(const char *refname, int force_create, struct strbuf *err)
{
	int ret;
	struct strbuf sb = STRBUF_INIT;

	ret = log_ref_setup(refname, &sb, err, force_create);
	strbuf_release(&sb);
	return ret;
}