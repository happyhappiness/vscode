static int parse_fragment(const char *line, unsigned long size,
			  struct patch *patch, struct fragment *fragment)
{
	int added, deleted;
	int len = linelen(line, size), offset;
	unsigned long oldlines, newlines;
	unsigned long leading, trailing;

	offset = parse_fragment_header(line, len, fragment);
	if (offset < 0)
		return -1;
	if (offset > 0 && patch->recount)
		recount_diff(line + offset, size - offset, fragment);
	oldlines = fragment->oldlines;
	newlines = fragment->newlines;
	leading = 0;
	trailing = 0;

	/* Parse the thing.. */
	line += len;
	size -= len;
	linenr++;
	added = deleted = 0;
	for (offset = len;
	     0 < size;
	     offset += len, size -= len, line += len, linenr++) {
		if (!oldlines && !newlines)
			break;
		len = linelen(line, size);
		if (!len || line[len-1] != '\n')
			return -1;
		switch (*line) {
		default:
			return -1;
		case '\n': /* newer GNU diff, an empty context line */
		case ' ':
			oldlines--;
			newlines--;
			if (!deleted && !added)
				leading++;
			trailing++;
			if (!apply_in_reverse &&
			    ws_error_action == correct_ws_error)
				check_whitespace(line, len, patch->ws_rule);
			break;
		case '-':
			if (apply_in_reverse &&
			    ws_error_action != nowarn_ws_error)
				check_whitespace(line, len, patch->ws_rule);
			deleted++;
			oldlines--;
			trailing = 0;
			break;
		case '+':
			if (!apply_in_reverse &&
			    ws_error_action != nowarn_ws_error)
				check_whitespace(line, len, patch->ws_rule);
			added++;
			newlines--;
			trailing = 0;
			break;

		/*
		 * We allow "\ No newline at end of file". Depending
                 * on locale settings when the patch was produced we
                 * don't know what this line looks like. The only
                 * thing we do know is that it begins with "\ ".
		 * Checking for 12 is just for sanity check -- any
		 * l10n of "\ No newline..." is at least that long.
		 */
		case '\\':
			if (len < 12 || memcmp(line, "\\ ", 2))
				return -1;
			break;
		}
	}
	if (oldlines || newlines)
		return -1;
	if (!deleted && !added)
		return -1;

	fragment->leading = leading;
	fragment->trailing = trailing;

	/*
	 * If a fragment ends with an incomplete line, we failed to include
	 * it in the above loop because we hit oldlines == newlines == 0
	 * before seeing it.
	 */
	if (12 < size && !memcmp(line, "\\ ", 2))
		offset += linelen(line, size);

	patch->lines_added += added;
	patch->lines_deleted += deleted;

	if (0 < patch->is_new && oldlines)
		return error(_("new file depends on old contents"));
	if (0 < patch->is_delete && newlines)
		return error(_("deleted file still has contents"));
	return offset;
}