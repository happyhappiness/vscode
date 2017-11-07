static void parse_cmd_option(const char *next)
{
	if (!strcmp(next, "no-deref"))
		update_flags |= REF_NODEREF;
	else
		die("option unknown: %s", next);
}