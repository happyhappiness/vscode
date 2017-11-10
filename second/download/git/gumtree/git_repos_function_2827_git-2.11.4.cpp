static int find_trailer_end(struct strbuf **lines, int patch_start)
{
	struct strbuf sb = STRBUF_INIT;
	int i, ignore_bytes;

	for (i = 0; i < patch_start; i++)
		strbuf_addbuf(&sb, lines[i]);
	ignore_bytes = ignore_non_trailer(&sb);
	strbuf_release(&sb);
	for (i = patch_start - 1; i >= 0 && ignore_bytes > 0; i--)
		ignore_bytes -= lines[i]->len;

	return i + 1;
}