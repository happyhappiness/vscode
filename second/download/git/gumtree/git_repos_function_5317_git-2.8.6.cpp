static void *anonymize_tag(const void *old, size_t *len)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "tag message %d", counter++);
	return strbuf_detach(&out, len);
}