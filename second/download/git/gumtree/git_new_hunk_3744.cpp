	if (n >= sizeof(buffer))
		die("protocol error: impossibly long line");

	write_or_die(fd, buffer, n);
}

static void http_status(struct strbuf *hdr, unsigned code, const char *msg)
{
	strbuf_addf(hdr, "Status: %u %s\r\n", code, msg);
}

static void hdr_str(struct strbuf *hdr, const char *name, const char *value)
{
	strbuf_addf(hdr, "%s: %s\r\n", name, value);
}

static void hdr_int(struct strbuf *hdr, const char *name, uintmax_t value)
{
	strbuf_addf(hdr, "%s: %" PRIuMAX "\r\n", name, value);
}

static void hdr_date(struct strbuf *hdr, const char *name, unsigned long when)
{
	const char *value = show_date(when, 0, DATE_MODE(RFC2822));
	hdr_str(hdr, name, value);
}

static void hdr_nocache(struct strbuf *hdr)
{
	hdr_str(hdr, "Expires", "Fri, 01 Jan 1980 00:00:00 GMT");
	hdr_str(hdr, "Pragma", "no-cache");
	hdr_str(hdr, "Cache-Control", "no-cache, max-age=0, must-revalidate");
}

static void hdr_cache_forever(struct strbuf *hdr)
{
	unsigned long now = time(NULL);
	hdr_date(hdr, "Date", now);
	hdr_date(hdr, "Expires", now + 31536000);
	hdr_str(hdr, "Cache-Control", "public, max-age=31536000");
}

static void end_headers(struct strbuf *hdr)
{
	strbuf_add(hdr, "\r\n", 2);
	write_or_die(1, hdr->buf, hdr->len);
	strbuf_release(hdr);
}

__attribute__((format (printf, 2, 3)))
static NORETURN void not_found(struct strbuf *hdr, const char *err, ...)
{
	va_list params;

	http_status(hdr, 404, "Not Found");
	hdr_nocache(hdr);
	end_headers(hdr);

	va_start(params, err);
	if (err && *err)
		vfprintf(stderr, err, params);
	va_end(params);
	exit(0);
}

__attribute__((format (printf, 2, 3)))
static NORETURN void forbidden(struct strbuf *hdr, const char *err, ...)
{
	va_list params;

	http_status(hdr, 403, "Forbidden");
	hdr_nocache(hdr);
	end_headers(hdr);

	va_start(params, err);
	if (err && *err)
		vfprintf(stderr, err, params);
	va_end(params);
	exit(0);
}

static void select_getanyfile(struct strbuf *hdr)
{
	if (!getanyfile)
		forbidden(hdr, "Unsupported service: getanyfile");
}

static void send_strbuf(struct strbuf *hdr,
			const char *type, struct strbuf *buf)
{
	hdr_int(hdr, content_length, buf->len);
	hdr_str(hdr, content_type, type);
	end_headers(hdr);
	write_or_die(1, buf->buf, buf->len);
}

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
