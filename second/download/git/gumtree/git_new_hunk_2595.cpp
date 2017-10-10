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
	strcpy(temp->hex, sha1_to_hex(sha1));
	temp->hex[40] = 0;
	sprintf(temp->mode, "%06o", mode);
	strbuf_release(&buf);
	strbuf_release(&template);
	free(path_dup);
