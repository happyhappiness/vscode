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
