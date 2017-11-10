static void handle_message_id(struct mailinfo *mi, const struct strbuf *line)
{
	if (mi->add_message_id)
		mi->message_id = strdup(line->buf);
}