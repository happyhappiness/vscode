 	if (width == ~0U)
 		die(_("positive width expected with the %%(align) atom"));
 	align->width = width;
 	string_list_clear(&params, 0);
 }
 
-static void if_atom_parser(struct used_atom *atom, const char *arg)
+static void if_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
 {
 	if (!arg) {
 		atom->u.if_then_else.cmp_status = COMPARE_NONE;
 		return;
 	} else if (skip_prefix(arg, "equals=", &atom->u.if_then_else.str)) {
 		atom->u.if_then_else.cmp_status = COMPARE_EQUAL;
