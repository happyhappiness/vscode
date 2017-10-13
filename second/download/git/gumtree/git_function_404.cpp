static int show_tag_object(const unsigned char *sha1, struct rev_info *rev)
{
	unsigned long size;
	enum object_type type;
	char *buf = read_sha1_file(sha1, &type, &size);
	int offset = 0;

	if (!buf)
		return error(_("Could not read object %s"), sha1_to_hex(sha1));

	assert(type == OBJ_TAG);
	while (offset < size && buf[offset] != '\n') {
		int new_offset = offset + 1;
		while (new_offset < size && buf[new_offset++] != '\n')
			; /* do nothing */
		if (starts_with(buf + offset, "tagger "))
			show_tagger(buf + offset + 7,
				    new_offset - offset - 7, rev);
		offset = new_offset;
	}

	if (offset < size)
		fwrite(buf + offset, size - offset, 1, rev->diffopt.file);
	free(buf);
	return 0;
}