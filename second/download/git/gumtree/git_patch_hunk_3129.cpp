 		if (!opts->quiet) {
 			if (old->path && advice_detached_head)
 				detach_advice(new->name);
 			describe_detached_head(_("HEAD is now at"), new->commit);
 		}
 	} else if (new->path) {	/* Switch branches. */
-		create_symref("HEAD", new->path, msg.buf);
+		if (create_symref("HEAD", new->path, msg.buf) < 0)
+			die(_("unable to update HEAD"));
 		if (!opts->quiet) {
 			if (old->path && !strcmp(new->path, old->path)) {
 				if (opts->new_branch_force)
 					fprintf(stderr, _("Reset branch '%s'\n"),
 						new->name);
 				else
