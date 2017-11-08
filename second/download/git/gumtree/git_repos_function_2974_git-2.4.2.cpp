static int write_strbuf(void *user_data, const void *data, size_t len)
{
	struct strbuf *sb = user_data;
	strbuf_add(sb, data, len);
	return len;
}