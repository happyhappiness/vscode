static void write_tag_body(int fd, const struct object_id *oid)
{
	unsigned long size;
	enum object_type type;
	char *buf, *sp;

	buf = read_sha1_file(oid->hash, &type, &size);
	if (!buf)
		return;
	/* skip header */
	sp = strstr(buf, "\n\n");

	if (!sp || !size || type != OBJ_TAG) {
		free(buf);
		return;
	}
	sp += 2; /* skip the 2 LFs */
	write_or_die(fd, sp, parse_signature(sp, buf + size - sp));

	free(buf);
}