static void prepare_image(struct image *image, char *buf, size_t len,
			  int prepare_linetable)
{
	const char *cp, *ep;

	memset(image, 0, sizeof(*image));
	image->buf = buf;
	image->len = len;

	if (!prepare_linetable)
		return;

	ep = image->buf + image->len;
	cp = image->buf;
	while (cp < ep) {
		const char *next;
		for (next = cp; next < ep && *next != '\n'; next++)
			;
		if (next < ep)
			next++;
		add_line_info(image, cp, next - cp, 0);
		cp = next;
	}
	image->line = image->line_allocated;
}