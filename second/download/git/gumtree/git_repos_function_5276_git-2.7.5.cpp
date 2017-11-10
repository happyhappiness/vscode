static void *anonymize_ref_component(const void *old, size_t *len)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "ref%d", counter++);
	return strbuf_detach(&out, len);
}