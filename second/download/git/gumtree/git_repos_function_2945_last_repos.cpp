static void get_root_part(struct strbuf *resolved, struct strbuf *remaining)
{
	int offset = offset_1st_component(remaining->buf);

	strbuf_reset(resolved);
	strbuf_add(resolved, remaining->buf, offset);
#ifdef GIT_WINDOWS_NATIVE
	convert_slashes(resolved->buf);
#endif
	strbuf_remove(remaining, 0, offset);
}