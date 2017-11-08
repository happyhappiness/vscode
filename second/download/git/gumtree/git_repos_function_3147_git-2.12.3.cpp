static void get_head(struct strbuf *hdr, char *arg)
{
	struct strbuf buf = STRBUF_INIT;

	select_getanyfile(hdr);
	head_ref_namespaced(show_head_ref, &buf);
	send_strbuf(hdr, "text/plain", &buf);
	strbuf_release(&buf);
}