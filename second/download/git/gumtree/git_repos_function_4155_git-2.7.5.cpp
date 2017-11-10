static int parse_sorting_string(const char *arg, struct ref_sorting **sorting_tail)
{
	struct ref_sorting *s;
	int len;

	s = xcalloc(1, sizeof(*s));
	s->next = *sorting_tail;
	*sorting_tail = s;

	if (*arg == '-') {
		s->reverse = 1;
		arg++;
	}
	if (skip_prefix(arg, "version:", &arg) ||
	    skip_prefix(arg, "v:", &arg))
		s->version = 1;

	len = strlen(arg);
	s->atom = parse_ref_filter_atom(arg, arg+len);

	return 0;
}