int parse_opt_ref_sorting(const struct option *opt, const char *arg, int unset)
{
	struct ref_sorting **sorting_tail = opt->value;
	struct ref_sorting *s;
	int len;

	if (!arg) /* should --no-sort void the list ? */
		return -1;

	s = xcalloc(1, sizeof(*s));
	s->next = *sorting_tail;
	*sorting_tail = s;

	if (*arg == '-') {
		s->reverse = 1;
		arg++;
	}
	len = strlen(arg);
	s->atom = parse_ref_filter_atom(arg, arg+len);
	return 0;
}