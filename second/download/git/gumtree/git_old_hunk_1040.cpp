	if (width == ~0U)
		die(_("positive width expected with the %%(align) atom"));
	align->width = width;
	string_list_clear(&params, 0);
}

static struct {
	const char *name;
	cmp_type cmp_type;
	void (*parser)(struct used_atom *atom, const char *arg);
} valid_atom[] = {
	{ "refname" },
	{ "objecttype" },
	{ "objectsize", FIELD_ULONG },
	{ "objectname", FIELD_STR, objectname_atom_parser },
	{ "tree" },
	{ "parent" },
	{ "numparent", FIELD_ULONG },
