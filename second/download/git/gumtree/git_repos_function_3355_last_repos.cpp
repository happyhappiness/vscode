static void send_local_file(struct strbuf *hdr, const char *the_type,
				const char *name)
{
	char *p = git_pathdup("%s", name);
	size_t buf_alloc = 8192;
	char *buf = xmalloc(buf_alloc);
	int fd;
	struct stat sb;

	fd = open(p, O_RDONLY);
	if (fd < 0)
		not_found(hdr, "Cannot open '%s': %s", p, strerror(errno));
	if (fstat(fd, &sb) < 0)
		die_errno("Cannot stat '%s'", p);

	hdr_int(hdr, content_length, sb.st_size);
	hdr_str(hdr, content_type, the_type);
	hdr_date(hdr, last_modified, sb.st_mtime);
	end_headers(hdr);

	for (;;) {
		ssize_t n = xread(fd, buf, buf_alloc);
		if (n < 0)
			die_errno("Cannot read '%s'", p);
		if (!n)
			break;
		write_or_die(1, buf, n);
	}
	close(fd);
	free(buf);
	free(p);
}