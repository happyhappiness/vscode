static void copy_request(const char *prog_name, int out)
{
	unsigned char *buf;
	ssize_t n = read_request(0, &buf);
	if (n < 0)
		die_errno("error reading request body");
	if (write_in_full(out, buf, n) != n)
		die("%s aborted reading request", prog_name);
	close(out);
	free(buf);
}