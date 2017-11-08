static void handle_message_id(const struct strbuf *line)
{
	if (add_message_id)
		message_id = strdup(line->buf);
}