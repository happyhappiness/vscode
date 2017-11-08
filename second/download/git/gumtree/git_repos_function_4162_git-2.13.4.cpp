static int reinterpret(const char *name, int namelen, int len,
		       struct strbuf *buf, unsigned allowed)
{
	/* we have extra data, which might need further processing */
	struct strbuf tmp = STRBUF_INIT;
	int used = buf->len;
	int ret;

	strbuf_add(buf, name + len, namelen - len);
	ret = interpret_branch_name(buf->buf, buf->len, &tmp, allowed);
	/* that data was not interpreted, remove our cruft */
	if (ret < 0) {
		strbuf_setlen(buf, used);
		return len;
	}
	strbuf_reset(buf);
	strbuf_addbuf(buf, &tmp);
	strbuf_release(&tmp);
	/* tweak for size of {-N} versus expanded ref name */
	return ret - used + len;
}