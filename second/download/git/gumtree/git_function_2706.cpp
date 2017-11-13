static void objectname_atom_parser(struct used_atom *atom, const char *arg)
{
	if (!arg)
		atom->u.objectname = O_FULL;
	else if (!strcmp(arg, "short"))
		atom->u.objectname = O_SHORT;
	else
		die(_("unrecognized %%(objectname) argument: %s"), arg);
}