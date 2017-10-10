 };
 
 struct atom_value {
 	const char *s;
 	union {
 		struct align align;
-		struct contents contents;
 	} u;
 	void (*handler)(struct atom_value *atomv, struct ref_formatting_state *state);
 	unsigned long ul; /* used for sorting when not FIELD_STR */
 };
 
 /*
- * An atom is a valid field atom listed above, possibly prefixed with
- * a "*" to denote deref_tag().
- *
- * We parse given format string and sort specifiers, and make a list
- * of properties that we need to extract out of objects.  ref_array_item
- * structure will hold an array of values extracted that can be
- * indexed with the "atom number", which is an index into this
- * array.
- */
-static const char **used_atom;
-static cmp_type *used_atom_type;
-static int used_atom_cnt, need_tagged, need_symref;
-static int need_color_reset_at_eol;
-
-/*
  * Used to parse format string and sort specifiers
  */
 int parse_ref_filter_atom(const char *atom, const char *ep)
 {
 	const char *sp;
+	const char *arg;
 	int i, at;
 
 	sp = atom;
 	if (*sp == '*' && sp < ep)
 		sp++; /* deref */
 	if (ep <= sp)
-		die("malformed field name: %.*s", (int)(ep-atom), atom);
+		die(_("malformed field name: %.*s"), (int)(ep-atom), atom);
 
 	/* Do we have the atom already used elsewhere? */
 	for (i = 0; i < used_atom_cnt; i++) {
-		int len = strlen(used_atom[i]);
-		if (len == ep - atom && !memcmp(used_atom[i], atom, len))
+		int len = strlen(used_atom[i].name);
+		if (len == ep - atom && !memcmp(used_atom[i].name, atom, len))
 			return i;
 	}
 
 	/* Is the atom a valid one? */
 	for (i = 0; i < ARRAY_SIZE(valid_atom); i++) {
 		int len = strlen(valid_atom[i].name);
