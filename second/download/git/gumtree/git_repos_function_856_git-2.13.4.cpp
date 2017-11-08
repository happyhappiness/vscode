static int verify_utf8(struct strbuf *buf)
{
	int ok = 1;
	long pos = 0;

	for (;;) {
		int bad;
		unsigned char c;
		unsigned char replace[2];

		bad = find_invalid_utf8(buf->buf + pos, buf->len - pos);
		if (bad < 0)
			return ok;
		pos += bad;
		ok = 0;
		c = buf->buf[pos];
		strbuf_remove(buf, pos, 1);

		/* We know 'c' must be in the range 128-255 */
		replace[0] = 0xc0 + (c >> 6);
		replace[1] = 0x80 + (c & 0x3f);
		strbuf_insert(buf, pos, replace, 2);
		pos += 2;
	}
}