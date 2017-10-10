		atom->u.if_then_else.cmp_status = COMPARE_UNEQUAL;
	} else {
		die(_("unrecognized %%(if) argument: %s"), arg);
	}
}

static void head_atom_parser(struct used_atom *atom, const char *arg)
{
	struct object_id unused;

	atom->u.head = resolve_refdup("HEAD", RESOLVE_REF_READING, unused.hash, NULL);
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
