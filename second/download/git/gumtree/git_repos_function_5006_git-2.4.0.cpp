static void *anonymize_path_component(const void *path, size_t *len)
{
	static int counter;
	struct strbuf out = STRBUF_INIT;
	strbuf_addf(&out, "path%d", counter++);
	return strbuf_detach(&out, len);
}