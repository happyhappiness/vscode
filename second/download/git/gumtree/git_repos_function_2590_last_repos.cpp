static void handle_patch(struct mailinfo *mi, const struct strbuf *line)
{
	fwrite(line->buf, 1, line->len, mi->patchfile);
	mi->patch_lines++;
}