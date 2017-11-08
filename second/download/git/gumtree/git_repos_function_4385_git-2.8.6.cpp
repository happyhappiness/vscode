static void set_commit_buffer_from_strbuf(struct commit *c, struct strbuf *sb)
{
	size_t len;
	void *buf = strbuf_detach(sb, &len);
	set_commit_buffer(c, buf, len);
}