static void rerere_io_putconflict(int ch, int size, struct rerere_io *io)
{
	char buf[64];

	while (size) {
		if (size < sizeof(buf) - 2) {
			memset(buf, ch, size);
			buf[size] = '\n';
			buf[size + 1] = '\0';
			size = 0;
		} else {
			int sz = sizeof(buf) - 1;
			if (size <= sz)
				sz -= (sz - size) + 1;
			memset(buf, ch, sz);
			buf[sz] = '\0';
			size -= sz;
		}
		rerere_io_putstr(buf, io);
	}
}