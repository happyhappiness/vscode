static void get_loose_object(struct strbuf *hdr, char *name)
{
	select_getanyfile(hdr);
	hdr_cache_forever(hdr);
	send_local_file(hdr, "application/x-git-loose-object", name);
}