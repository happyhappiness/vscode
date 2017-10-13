tatic void show_tag_lines(const struct object_id *oid, int lines)
{
	int i;
	unsigned long size;
	enum object_type type;
	char *buf, *sp, *eol;
	size_t len;

	buf = read_sha1_file(oid->hash, &type, &size);
	if (!buf)
		die_errno("unable to read object %s", oid_to_hex(oid));
	if (type != OBJ_COMMIT && type != OBJ_TAG)
		goto free_return;
	if (!size)
		die("an empty %s object %s?",
		    typename(type), oid_to_hex(oid));

	/* skip header */
	sp = strstr(buf, "\n\n");
	if (!sp)
		goto free_return;

	/* only take up to "lines" lines, and strip the signature from a tag */
	if (type == OBJ_TAG)
		size = parse_signature(buf, size);
	for (i = 0, sp += 2; i < lines && sp < buf + size; i++) {
		if (i)
			printf("\n    ");
		eol = memchr(sp, '\n', size - (sp - buf));
		len = eol ? eol - sp : size - (sp - buf);
		fwrite(sp, len, 1, stdout);
		if (!eol)
			break;
		sp = eol + 1;
	}
free_return:
	free(buf);
}