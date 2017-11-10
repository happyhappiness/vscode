static int store_write_pair(int fd, const char *key, const char *value)
{
	int i, success;
	int length = strlen(key + store.baselen + 1);
	const char *quote = "";
	struct strbuf sb = STRBUF_INIT;

	/*
	 * Check to see if the value needs to be surrounded with a dq pair.
	 * Note that problematic characters are always backslash-quoted; this
	 * check is about not losing leading or trailing SP and strings that
	 * follow beginning-of-comment characters (i.e. ';' and '#') by the
	 * configuration parser.
	 */
	if (value[0] == ' ')
		quote = "\"";
	for (i = 0; value[i]; i++)
		if (value[i] == ';' || value[i] == '#')
			quote = "\"";
	if (i && value[i - 1] == ' ')
		quote = "\"";

	strbuf_addf(&sb, "\t%.*s = %s",
		    length, key + store.baselen + 1, quote);

	for (i = 0; value[i]; i++)
		switch (value[i]) {
		case '\n':
			strbuf_addstr(&sb, "\\n");
			break;
		case '\t':
			strbuf_addstr(&sb, "\\t");
			break;
		case '"':
		case '\\':
			strbuf_addch(&sb, '\\');
		default:
			strbuf_addch(&sb, value[i]);
			break;
		}
	strbuf_addf(&sb, "%s\n", quote);

	success = write_in_full(fd, sb.buf, sb.len) == sb.len;
	strbuf_release(&sb);

	return success;
}