static void mark_expected_rev(char *bisect_rev_hex)
{
	int len = strlen(bisect_rev_hex);
	const char *filename = git_path("BISECT_EXPECTED_REV");
	int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);

	if (fd < 0)
		die_errno("could not create file '%s'", filename);

	bisect_rev_hex[len] = '\n';
	write_or_die(fd, bisect_rev_hex, len + 1);
	bisect_rev_hex[len] = '\0';

	if (close(fd) < 0)
		die("closing file %s: %s", filename, strerror(errno));
}