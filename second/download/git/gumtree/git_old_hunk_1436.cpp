
static void file_change_m(const char *p, struct branch *b)
{
	static struct strbuf uq = STRBUF_INIT;
	const char *endp;
	struct object_entry *oe;
	unsigned char sha1[20];
	uint16_t mode, inline_data = 0;

	p = get_mode(p, &mode);
	if (!p)
		die("Corrupt mode: %s", command_buf.buf);
	switch (mode) {
