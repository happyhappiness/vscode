static struct grep_expr *compile_pattern_expr(struct grep_pat **list)
{
	return compile_pattern_or(list);
}