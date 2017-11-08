static void comment_lines(struct strbuf *buf)
{
	char *msg;
	size_t len;

	msg = strbuf_detach(buf, &len);
	strbuf_add_commented_lines(buf, msg, len);
	free(msg);
}