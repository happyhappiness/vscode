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
