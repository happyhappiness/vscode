static int read_magic(struct line_buffer *in, off_t *len)
{
	static const char magic[] = {'S', 'V', 'N', '\0'};
	struct strbuf sb = STRBUF_INIT;

	if (read_chunk(in, len, &sb, sizeof(magic))) {
		strbuf_release(&sb);
		return -1;
	}
	if (memcmp(sb.buf, magic, sizeof(magic))) {
		strbuf_release(&sb);
		return error("invalid delta: unrecognized file type");
	}
	strbuf_release(&sb);
	return 0;
}