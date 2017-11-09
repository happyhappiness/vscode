static int strbuf_add_le(struct strbuf *sb, size_t size, uintmax_t n)
{
	while (size-- > 0) {
		strbuf_addch(sb, n & 0xff);
		n >>= 8;
	}
	return -!!n;
}