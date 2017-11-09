static void fill_sha1_path(struct strbuf *buf, const unsigned char *sha1)
{
	int i;
	for (i = 0; i < 20; i++) {
		static char hex[] = "0123456789abcdef";
		unsigned int val = sha1[i];
		strbuf_addch(buf, hex[val >> 4]);
		strbuf_addch(buf, hex[val & 0xf]);
		if (!i)
			strbuf_addch(buf, '/');
	}
}