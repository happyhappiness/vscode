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