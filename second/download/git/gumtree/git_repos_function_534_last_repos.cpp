static void remote_ref_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
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