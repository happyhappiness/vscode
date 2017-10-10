  * Used to parse format string and sort specifiers
  */
 int parse_ref_filter_atom(const char *atom, const char *ep)
 {
 	const char *sp;
 	const char *arg;
-	int i, at;
+	int i, at, atom_len;
 
 	sp = atom;
 	if (*sp == '*' && sp < ep)
 		sp++; /* deref */
 	if (ep <= sp)
 		die(_("malformed field name: %.*s"), (int)(ep-atom), atom);
