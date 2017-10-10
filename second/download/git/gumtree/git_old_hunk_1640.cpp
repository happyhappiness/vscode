		} objectname;
		struct refname_atom refname;
		char *head;
	} u;
} *used_atom;
static int used_atom_cnt, need_tagged, need_symref;
static int need_color_reset_at_eol;

static void color_atom_parser(struct used_atom *atom, const char *color_value)
{
	if (!color_value)
		die(_("expected format: %%(color:<color>)"));
	if (color_parse(color_value, atom->u.color) < 0)
		die(_("unrecognized color: %%(color:%s)"), color_value);
}

static void refname_atom_parser_internal(struct refname_atom *atom,
					 const char *arg, const char *name)
{
	if (!arg)
