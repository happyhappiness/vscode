static void get_next_component(struct strbuf *next, struct strbuf *remaining)
{
	char *start = NULL;
	char *end = NULL;

	strbuf_reset(next);

	/* look for the next component */
	/* Skip sequences of multiple path-separators */
	for (start = remaining->buf; is_dir_sep(*start); start++)
		; /* nothing */
	/* Find end of the path component */
	for (end = start; *end && !is_dir_sep(*end); end++)
		; /* nothing */

	strbuf_add(next, start, end - start);
	/* remove the component from 'remaining' */
	strbuf_remove(remaining, 0, end - remaining->buf);
}