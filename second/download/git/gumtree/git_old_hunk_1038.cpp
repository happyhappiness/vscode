	if (!color_value)
		die(_("expected format: %%(color:<color>)"));
	if (color_parse(color_value, atom->u.color) < 0)
		die(_("unrecognized color: %%(color:%s)"), color_value);
}

static void remote_ref_atom_parser(struct used_atom *atom, const char *arg)
{
	if (!arg)
		atom->u.remote_ref = RR_NORMAL;
	else if (!strcmp(arg, "short"))
		atom->u.remote_ref = RR_SHORTEN;
	else if (!strcmp(arg, "track"))
		atom->u.remote_ref = RR_TRACK;
	else if (!strcmp(arg, "trackshort"))
		atom->u.remote_ref = RR_TRACKSHORT;
	else
		die(_("unrecognized format: %%(%s)"), atom->name);
}

static void body_atom_parser(struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(body) does not take arguments"));
