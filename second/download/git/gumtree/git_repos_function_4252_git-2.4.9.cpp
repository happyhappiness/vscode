static int opt_parse_sort(const struct option *opt, const char *arg, int unset)
{
	struct ref_sort **sort_tail = opt->value;
	struct ref_sort *s;
	int len;

	if (!arg) /* should --no-sort void the list ? */
		return -1;

	s = xcalloc(1, sizeof(*s));
	s->next = *sort_tail;
	*sort_tail = s;

	if (*arg == '-') {
		s->reverse = 1;
		arg++;
	}
	len = strlen(arg);
	s->atom = parse_atom(arg, arg+len);
	return 0;
}