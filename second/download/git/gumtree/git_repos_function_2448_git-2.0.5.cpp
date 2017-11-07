static void write_packed_entry(int fd, char *refname, unsigned char *sha1,
			       unsigned char *peeled)
{
	char line[PATH_MAX + 100];
	int len;

	len = snprintf(line, sizeof(line), "%s %s\n",
		       sha1_to_hex(sha1), refname);
	/* this should not happen but just being defensive */
	if (len > sizeof(line))
		die("too long a refname '%s'", refname);
	write_or_die(fd, line, len);

	if (peeled) {
		if (snprintf(line, sizeof(line), "^%s\n",
			     sha1_to_hex(peeled)) != PEELED_LINE_LENGTH)
			die("internal error");
		write_or_die(fd, line, PEELED_LINE_LENGTH);
	}
}