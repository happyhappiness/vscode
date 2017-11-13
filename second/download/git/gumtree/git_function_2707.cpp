static void align_atom_parser(struct used_atom *atom, const char *arg)
{
	struct align *align = &atom->u.align;
	struct string_list params = STRING_LIST_INIT_DUP;
	int i;
	unsigned int width = ~0U;

	if (!arg)
		die(_("expected format: %%(align:<width>,<position>)"));

	align->position = ALIGN_LEFT;

	string_list_split(&params, arg, ',', -1);
	for (i = 0; i < params.nr; i++) {
		const char *s = params.items[i].string;
		int position;

		if (skip_prefix(s, "position=", &s)) {
			position = parse_align_position(s);
			if (position < 0)
				die(_("unrecognized position:%s"), s);
			align->position = position;
		} else if (skip_prefix(s, "width=", &s)) {
			if (strtoul_ui(s, 10, &width))
				die(_("unrecognized width:%s"), s);
		} else if (!strtoul_ui(s, 10, &width))
			;
		else if ((position = parse_align_position(s)) >= 0)
			align->position = position;
		else
			die(_("unrecognized %%(align) argument: %s"), s);
	}

	if (width == ~0U)
		die(_("positive width expected with the %%(align) atom"));
	align->width = width;
	string_list_clear(&params, 0);
}