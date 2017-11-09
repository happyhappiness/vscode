void write_bigbuf(int f, const char *buf, size_t len)
{
	size_t half_max = (iobuf.out.size - iobuf.out_empty_len) / 2;

	while (len > half_max + 1024) {
		write_buf(f, buf, half_max);
		buf += half_max;
		len -= half_max;
	}

	write_buf(f, buf, len);
}