 						    RESOLVE_REF_READING,
 						    oid.hash, NULL);
 			fake_av[1] = NULL;
 			av = fake_av;
 			ac = 1;
 			if (!*av)
-				die("no branches given, and HEAD is not valid");
+				die(_("no branches given, and HEAD is not valid"));
 		}
 		if (ac != 1)
-			die("--reflog option needs one branch name");
+			die(_("--reflog option needs one branch name"));
 
 		if (MAX_REVS < reflog)
-			die("Only %d entries can be shown at one time.",
-			    MAX_REVS);
+			die(Q_("only %d entry can be shown at one time.",
+			       "only %d entries can be shown at one time.",
+			       MAX_REVS), MAX_REVS);
 		if (!dwim_ref(*av, strlen(*av), oid.hash, &ref))
-			die("No such ref %s", *av);
+			die(_("no such ref %s"), *av);
 
 		/* Has the base been specified? */
 		if (reflog_base) {
 			char *ep;
 			base = strtoul(reflog_base, &ep, 10);
 			if (*ep) {
