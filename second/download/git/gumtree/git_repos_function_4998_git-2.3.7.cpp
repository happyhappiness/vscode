static void *anonymize_ident(const void *old, size_t *len)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "User %d <user%d@example.com>", counter, counter);
	counter++;
	return strbuf_detach(&out, len);
}