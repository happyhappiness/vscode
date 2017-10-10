		if (atom->u.objectname.length < MINIMUM_ABBREV)
			atom->u.objectname.length = MINIMUM_ABBREV;
	} else
		die(_("unrecognized %%(objectname) argument: %s"), arg);
}

static void refname_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	refname_atom_parser_internal(&atom->u.refname, arg, atom->name);
}

static align_type parse_align_position(const char *s)
{
