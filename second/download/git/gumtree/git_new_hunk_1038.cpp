	if (!color_value)
		die(_("expected format: %%(color:<color>)"));
	if (color_parse(color_value, atom->u.color) < 0)
		die(_("unrecognized color: %%(color:%s)"), color_value);
}

static void refname_atom_parser_internal(struct refname_atom *atom,
					 const char *arg, const char *name)
{
	if (!arg)
		atom->option = R_NORMAL;
	else if (!strcmp(arg, "short"))
		atom->option = R_SHORT;
	else if (skip_prefix(arg, "lstrip=", &arg) ||
		 skip_prefix(arg, "strip=", &arg)) {
		atom->option = R_LSTRIP;
		if (strtol_i(arg, 10, &atom->lstrip))
			die(_("Integer value expected refname:lstrip=%s"), arg);
	} else if (skip_prefix(arg, "rstrip=", &arg)) {
		atom->option = R_RSTRIP;
		if (strtol_i(arg, 10, &atom->rstrip))
			die(_("Integer value expected refname:rstrip=%s"), arg);
	} else
		die(_("unrecognized %%(%s) argument: %s"), name, arg);
}

static void remote_ref_atom_parser(struct used_atom *atom, const char *arg)
{
	struct string_list params = STRING_LIST_INIT_DUP;
	int i;

	if (!arg) {
		atom->u.remote_ref.option = RR_REF;
		refname_atom_parser_internal(&atom->u.remote_ref.refname,
					     arg, atom->name);
		return;
	}

	atom->u.remote_ref.nobracket = 0;
	string_list_split(&params, arg, ',', -1);

	for (i = 0; i < params.nr; i++) {
		const char *s = params.items[i].string;

		if (!strcmp(s, "track"))
			atom->u.remote_ref.option = RR_TRACK;
		else if (!strcmp(s, "trackshort"))
			atom->u.remote_ref.option = RR_TRACKSHORT;
		else if (!strcmp(s, "nobracket"))
			atom->u.remote_ref.nobracket = 1;
		else {
			atom->u.remote_ref.option = RR_REF;
			refname_atom_parser_internal(&atom->u.remote_ref.refname,
						     arg, atom->name);
		}
	}

	string_list_clear(&params, 0);
}

static void body_atom_parser(struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(body) does not take arguments"));
