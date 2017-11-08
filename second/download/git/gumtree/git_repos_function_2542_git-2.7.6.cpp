static int find_trailer_start(struct strbuf **lines, int count)
{
	int start, end_of_title, only_spaces = 1;

	/* The first paragraph is the title and cannot be trailers */
	for (start = 0; start < count; start++) {
		if (lines[start]->buf[0] == comment_line_char)
			continue;
		if (contains_only_spaces(lines[start]->buf))
			break;
	}
	end_of_title = start;

	/*
	 * Get the start of the trailers by looking starting from the end
	 * for a line with only spaces before lines with one separator.
	 */
	for (start = count - 1; start >= end_of_title; start--) {
		if (lines[start]->buf[0] == comment_line_char)
			continue;
		if (contains_only_spaces(lines[start]->buf)) {
			if (only_spaces)
				continue;
			return start + 1;
		}
		if (strcspn(lines[start]->buf, separators) < lines[start]->len) {
			if (only_spaces)
				only_spaces = 0;
			continue;
		}
		return count;
	}

	return only_spaces ? count : 0;
}