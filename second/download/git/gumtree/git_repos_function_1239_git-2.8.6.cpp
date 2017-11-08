static void prep_temp_blob(const char *path, struct diff_tempfile *temp,
			   void *blob,
			   unsigned long size,
			   const unsigned char *sha1,
			   int mode)
{
	int fd;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf template = STRBUF_INIT;
	char *path_dup = xstrdup(path);
	const char *base = basename(path_dup);

	/* Generate "XXXXXX_basename.ext" */
	strbuf_addstr(&template, "XXXXXX_");
	strbuf_addstr(&template, base);

	fd = mks_tempfile_ts(&temp->tempfile, template.buf, strlen(base) + 1);
	if (fd < 0)
		die_errno("unable to create temp-file");
	if (convert_to_working_tree(path,
			(const char *)blob, (size_t)size, &buf)) {
		blob = buf.buf;
		size = buf.len;
	}
	if (write_in_full(fd, blob, size) != size)
		die_errno("unable to write temp-file");
	close_tempfile(&temp->tempfile);
	temp->name = get_tempfile_path(&temp->tempfile);
	sha1_to_hex_r(temp->hex, sha1);
	xsnprintf(temp->mode, sizeof(temp->mode), "%06o", mode);
	strbuf_release(&buf);
	strbuf_release(&template);
	free(path_dup);
}