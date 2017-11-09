int grep_buffer(struct grep_opt *opt, char *buf, unsigned long size)
{
	struct grep_source gs;
	int r;

	grep_source_init(&gs, GREP_SOURCE_BUF, NULL, NULL, NULL);
	gs.buf = buf;
	gs.size = size;

	r = grep_source(opt, &gs);

	grep_source_clear(&gs);
	return r;
}