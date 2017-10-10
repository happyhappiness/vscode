		} objectname;
		struct refname_atom refname;
		char *head;
	} u;
} *used_atom;
static int used_atom_cnt, need_tagged, need_symref;

static void color_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *color_value)
{
	if (!color_value)
		die(_("expected format: %%(color:<color>)"));
	if (color_parse(color_value, atom->u.color) < 0)
		die(_("unrecognized color: %%(color:%s)"), color_value);
	/*
	 * We check this after we've parsed the color, which lets us complain
	 * about syntactically bogus color names even if they won't be used.
	 */
	if (!want_color(format->use_color))
		color_parse("", atom->u.color);
}

static void refname_atom_parser_internal(struct refname_atom *atom,
					 const char *arg, const char *name)
{
	if (!arg)
