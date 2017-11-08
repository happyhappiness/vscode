static int match_order(const char *path)
{
	int i;
	static struct strbuf p = STRBUF_INIT;

	for (i = 0; i < order_cnt; i++) {
		strbuf_reset(&p);
		strbuf_addstr(&p, path);
		while (p.buf[0]) {
			char *cp;
			if (!wildmatch(order[i], p.buf, 0))
				return i;
			cp = strrchr(p.buf, '/');
			if (!cp)
				break;
			*cp = 0;
		}
	}
	return order_cnt;
}