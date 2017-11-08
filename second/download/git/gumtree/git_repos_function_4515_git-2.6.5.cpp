static int message_is_empty(struct strbuf *sb)
{
	if (cleanup_mode == CLEANUP_NONE && sb->len)
		return 0;
	return rest_is_empty(sb, 0);
}