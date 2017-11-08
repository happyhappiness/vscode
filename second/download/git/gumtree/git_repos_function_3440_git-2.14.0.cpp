int for_each_namespaced_ref(each_ref_fn fn, void *cb_data)
{
	struct strbuf buf = STRBUF_INIT;
	int ret;
	strbuf_addf(&buf, "%srefs/", get_git_namespace());
	ret = do_for_each_ref(get_main_ref_store(),
			      buf.buf, fn, 0, 0, cb_data);
	strbuf_release(&buf);
	return ret;
}