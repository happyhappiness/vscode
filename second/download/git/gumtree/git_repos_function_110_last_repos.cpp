static void parse_commit_message(struct format_commit_context *c)
{
	const char *msg = c->message + c->message_off;
	const char *start = c->message;

	msg = skip_blank_lines(msg);
	c->subject_off = msg - start;

	msg = format_subject(NULL, msg, NULL);
	msg = skip_blank_lines(msg);
	c->body_off = msg - start;

	c->commit_message_parsed = 1;
}