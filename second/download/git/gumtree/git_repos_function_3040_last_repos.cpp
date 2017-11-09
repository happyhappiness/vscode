static int after_or_end(enum action_where where)
{
	return (where == WHERE_AFTER) || (where == WHERE_END);
}