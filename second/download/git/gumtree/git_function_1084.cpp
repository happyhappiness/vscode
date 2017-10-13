static void objectname_atom_parser(struct used_atom *atom, const char *arg)
{
	if (!arg)
		atom->u.objectname.option = O_FULL;
	else if (!strcmp(arg, "short"))
		atom->u.objectname.option = O_SHORT;
	else if (skip_prefix(arg, "short=", &arg)) {
		atom->u.objectname.option = O_LENGTH;
		if (strtoul_ui(arg, 10, &atom->u.objectname.length) ||
		    atom->u.objectname.length == 0)
			die(_("positive value expected objectname:short=%s"), arg);
		if (atom->u.objectname.length < MINIMUM_ABBREV)
			atom->u.objectname.length = MINIMUM_ABBREV;
	} else
		die(_("unrecognized %%(objectname) argument: %s"), arg);
}