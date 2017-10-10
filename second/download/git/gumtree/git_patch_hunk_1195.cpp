 	} else
 		die(_("unrecognized %%(objectname) argument: %s"), arg);
 }
 
 static void refname_atom_parser(struct used_atom *atom, const char *arg)
 {
-	return refname_atom_parser_internal(&atom->u.refname, arg, atom->name);
+	refname_atom_parser_internal(&atom->u.refname, arg, atom->name);
 }
 
 static align_type parse_align_position(const char *s)
 {
 	if (!strcmp(s, "right"))
 		return ALIGN_RIGHT;
