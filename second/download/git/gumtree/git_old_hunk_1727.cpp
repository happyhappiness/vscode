 * already in buf[] -- normally that should begin with
 * the Unix "From " line.  Write it into the specified
 * file.
 */
static int split_one(FILE *mbox, const char *name, int allow_bare)
{
	FILE *output = NULL;
	int fd;
	int status = 0;
	int is_bare = !is_from_line(buf.buf, buf.len);

	if (is_bare && !allow_bare)
		goto corrupt;

	fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0666);
	if (fd < 0)
		die_errno("cannot open output file '%s'", name);
	output = xfdopen(fd, "w");

	/* Copy it out, while searching for a line that begins with
