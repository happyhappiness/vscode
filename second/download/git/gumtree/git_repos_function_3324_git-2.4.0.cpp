static void set_shortened_ref(struct strbuf *buf, const char *ref)
{
	char *s = shorten_unambiguous_ref(ref, 0);
	strbuf_reset(buf);
	strbuf_addstr(buf, s);
	free(s);
}