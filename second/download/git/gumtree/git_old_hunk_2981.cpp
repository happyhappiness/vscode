	*sorting_tail = s;

	if (*arg == '-') {
		s->reverse = 1;
		arg++;
	}
	len = strlen(arg);
	s->atom = parse_ref_filter_atom(arg, arg+len);
	return 0;
}
