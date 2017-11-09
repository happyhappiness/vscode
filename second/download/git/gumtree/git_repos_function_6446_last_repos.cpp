static int show_one_reflog_ent(struct strbuf *sb, each_reflog_ent_fn fn, void *cb_data)
{
	struct object_id ooid, noid;
	char *email_end, *message;
	timestamp_t timestamp;
	int tz;
	const char *p = sb->buf;

	/* old SP new SP name <email> SP time TAB msg LF */
	if (!sb->len || sb->buf[sb->len - 1] != '\n' ||
	    parse_oid_hex(p, &ooid, &p) || *p++ != ' ' ||
	    parse_oid_hex(p, &noid, &p) || *p++ != ' ' ||
	    !(email_end = strchr(p, '>')) ||
	    email_end[1] != ' ' ||
	    !(timestamp = parse_timestamp(email_end + 2, &message, 10)) ||
	    !message || message[0] != ' ' ||
	    (message[1] != '+' && message[1] != '-') ||
	    !isdigit(message[2]) || !isdigit(message[3]) ||
	    !isdigit(message[4]) || !isdigit(message[5]))
		return 0; /* corrupt? */
	email_end[1] = '\0';
	tz = strtol(message + 1, NULL, 10);
	if (message[6] != '\t')
		message += 6;
	else
		message += 7;
	return fn(&ooid, &noid, p, timestamp, tz, message, cb_data);
}