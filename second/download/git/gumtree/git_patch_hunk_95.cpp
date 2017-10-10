 		if (e->flags & UNINTERESTING)
 			continue;
 
 		if (dwim_ref(e->name, strlen(e->name), sha1, &full_name) != 1)
 			continue;
 
+		if (refspecs) {
+			char *private;
+			private = apply_refspecs(refspecs, refspecs_nr, full_name);
+			if (private) {
+				free(full_name);
+				full_name = private;
+			}
+		}
+
 		commit = get_commit(e, full_name);
 		if (!commit) {
 			warning("%s: Unexpected object of type %s, skipping.",
 				e->name,
 				typename(e->item->type));
 			continue;
