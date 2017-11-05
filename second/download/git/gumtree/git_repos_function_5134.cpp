static void handle_patch(const struct strbuf *line)
{
	fwrite(line->buf, 1, line->len, patchfile);
	patch_lines++;
}