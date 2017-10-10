 		if (strtol_i(arg, 10, &atom->rstrip))
 			die(_("Integer value expected refname:rstrip=%s"), arg);
 	} else
 		die(_("unrecognized %%(%s) argument: %s"), name, arg);
 }
 
-static void remote_ref_atom_parser(struct used_atom *atom, const char *arg)
+static void remote_ref_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
 {
 	struct string_list params = STRING_LIST_INIT_DUP;
 	int i;
 
 	if (!arg) {
 		atom->u.remote_ref.option = RR_REF;
