static void get_idx_file(struct strbuf *hdr, char *name)
{
	select_getanyfile(hdr);
	hdr_cache_forever(hdr);
	send_local_file(hdr, "application/x-git-packed-objects-toc", name);
}