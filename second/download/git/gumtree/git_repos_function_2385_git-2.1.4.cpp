static void get_head(char *arg)
{
	struct strbuf buf = STRBUF_INIT;

	select_getanyfile();
	head_ref_namespaced(show_head_ref, &buf);
	send_strbuf("text/plain", &buf);
	strbuf_release(&buf);
}