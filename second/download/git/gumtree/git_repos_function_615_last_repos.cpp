void parse_ref_sorting(struct ref_sorting **sorting_tail, const char *arg)
{
	struct ref_sorting *s;

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
	s->atom = parse_sorting_atom(arg);
}