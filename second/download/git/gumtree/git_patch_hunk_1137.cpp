 	const char *ref;
 	init_notes(NULL, NULL, NULL, flags);
 	t = &default_notes_tree;
 
 	ref = (flags & NOTES_INIT_WRITABLE) ? t->update_ref : t->ref;
 	if (!starts_with(ref, "refs/notes/"))
-		/* TRANSLATORS: the first %s will be replaced by a
-		   git notes command: 'add', 'merge', 'remove', etc.*/
+		/*
+		 * TRANSLATORS: the first %s will be replaced by a git
+		 * notes command: 'add', 'merge', 'remove', etc.
+		 */
 		die(_("refusing to %s notes in %s (outside of refs/notes/)"),
 		    subcommand, ref);
 	return t;
 }
 
 static int list(int argc, const char **argv, const char *prefix)
