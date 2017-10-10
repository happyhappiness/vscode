		die(_("unrecognized %%(contents) argument: %s"), arg);
}

static void objectname_atom_parser(struct used_atom *atom, const char *arg)
{
	if (!arg)
		atom->u.objectname = O_FULL;
	else if (!strcmp(arg, "short"))
		atom->u.objectname = O_SHORT;
	else
		die(_("unrecognized %%(objectname) argument: %s"), arg);
}

static align_type parse_align_position(const char *s)
{
	if (!strcmp(s, "right"))
		return ALIGN_RIGHT;
	else if (!strcmp(s, "middle"))
		return ALIGN_MIDDLE;
