static void handle_attr_line(struct attr_stack *res,
			     const char *line,
			     const char *src,
			     int lineno,
			     int macro_ok)
{
	struct match_attr *a;

	a = parse_attr_line(line, src, lineno, macro_ok);
	if (!a)
		return;
	ALLOC_GROW(res->attrs, res->num_matches + 1, res->alloc);
	res->attrs[res->num_matches++] = a;
}