		}
	}

	string_list_clear(&params, 0);
}

static void body_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(body) does not take arguments"));
	atom->u.contents.option = C_BODY_DEP;
}

static void subject_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(subject) does not take arguments"));
	atom->u.contents.option = C_SUB;
}

static void trailers_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(trailers) does not take arguments"));
	atom->u.contents.option = C_TRAILERS;
}

static void contents_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	if (!arg)
		atom->u.contents.option = C_BARE;
	else if (!strcmp(arg, "body"))
		atom->u.contents.option = C_BODY;
	else if (!strcmp(arg, "signature"))
