static const char *parse_ref_line(struct strbuf *line, struct object_id *oid)
{
	const char *ref;

	if (parse_oid_hex(line->buf, oid, &ref) < 0)
		return NULL;
	if (!isspace(*ref++))
		return NULL;

	if (isspace(*ref))
		return NULL;

	if (line->buf[line->len - 1] != '\n')
		return NULL;
	line->buf[--line->len] = 0;

	return ref;
}