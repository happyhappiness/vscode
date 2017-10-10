}

static int grab_objectname(const char *name, const unsigned char *sha1,
			   struct atom_value *v, struct used_atom *atom)
{
	if (starts_with(name, "objectname")) {
		if (atom->u.objectname == O_SHORT) {
			v->s = xstrdup(find_unique_abbrev(sha1, DEFAULT_ABBREV));
			return 1;
		} else if (atom->u.objectname == O_FULL) {
			v->s = xstrdup(sha1_to_hex(sha1));
			return 1;
		} else
			die("BUG: unknown %%(objectname) option");
	}
	return 0;
}

