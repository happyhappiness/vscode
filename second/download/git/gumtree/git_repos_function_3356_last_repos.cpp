static void get_text_file(struct strbuf *hdr, char *name)
{
	select_getanyfile(hdr);
	hdr_nocache(hdr);
	send_local_file(hdr, "text/plain", name);
}