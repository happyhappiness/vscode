 		if (strtoul_ui(arg, 10, &atom->u.contents.nlines))
 			die(_("positive value expected contents:lines=%s"), arg);
 	} else
 		die(_("unrecognized %%(contents) argument: %s"), arg);
 }
 
-static void objectname_atom_parser(struct used_atom *atom, const char *arg)
+static void objectname_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
 {
 	if (!arg)
 		atom->u.objectname.option = O_FULL;
 	else if (!strcmp(arg, "short"))
 		atom->u.objectname.option = O_SHORT;
 	else if (skip_prefix(arg, "short=", &arg)) {
