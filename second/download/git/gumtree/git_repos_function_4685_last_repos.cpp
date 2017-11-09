static const char *parse_element_magic(unsigned *magic, int *prefix_len,
				       struct pathspec_item *item,
				       const char *elem)
{
	if (elem[0] != ':' || get_literal_global())
		return elem; /* nothing to do */
	else if (elem[1] == '(')
		/* longhand */
		return parse_long_magic(magic, prefix_len, item, elem);
	else
		/* shorthand */
		return parse_short_magic(magic, elem);
}