static int is_tag_in_date_range(struct object *tag, struct rev_info *revs)
{
	unsigned long size;
	enum object_type type;
	char *buf, *line, *lineend;
	unsigned long date;

	if (revs->max_age == -1 && revs->min_age == -1)
		return 1;

	buf = read_sha1_file(tag->sha1, &type, &size);
	if (!buf)
		return 1;
	line = memmem(buf, size, "\ntagger ", 8);
	if (!line++)
		return 1;
	lineend = memchr(line, buf + size - line, '\n');
	line = memchr(line, lineend ? lineend - line : buf + size - line, '>');
	if (!line++)
		return 1;
	date = strtoul(line, NULL, 10);
	free(buf);
	return (revs->max_age == -1 || revs->max_age < date) &&
		(revs->min_age == -1 || revs->min_age > date);
}