static void raw_read_buf(char *buf, size_t len)
{
	size_t pos = iobuf.in.pos;
	char *data = perform_io(len, PIO_INPUT_AND_CONSUME);
	if (iobuf.in.pos <= pos && len) {
		size_t siz = len - iobuf.in.pos;
		memcpy(buf, data, siz);
		memcpy(buf + siz, iobuf.in.buf, iobuf.in.pos);
	} else
		memcpy(buf, data, len);
}