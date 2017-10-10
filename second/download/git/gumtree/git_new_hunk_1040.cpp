	if (width == ~0U)
		die(_("positive width expected with the %%(align) atom"));
	align->width = width;
	string_list_clear(&params, 0);
}

static void if_atom_parser(struct used_atom *atom, const char *arg)
{
	if (!arg) {
		atom->u.if_then_else.cmp_status = COMPARE_NONE;
		return;
	} else if (skip_prefix(arg, "equals=", &atom->u.if_then_else.str)) {
		atom->u.if_then_else.cmp_status = COMPARE_EQUAL;
	} else if (skip_prefix(arg, "notequals=", &atom->u.if_then_else.str)) {
		atom->u.if_then_else.cmp_status = COMPARE_UNEQUAL;
	} else {
		die(_("unrecognized %%(if) argument: %s"), arg);
	}
}


static struct {
	const char *name;
	cmp_type cmp_type;
	void (*parser)(struct used_atom *atom, const char *arg);
} valid_atom[] = {
	{ "refname" , FIELD_STR, refname_atom_parser },
	{ "objecttype" },
	{ "objectsize", FIELD_ULONG },
	{ "objectname", FIELD_STR, objectname_atom_parser },
	{ "tree" },
	{ "parent" },
	{ "numparent", FIELD_ULONG },
