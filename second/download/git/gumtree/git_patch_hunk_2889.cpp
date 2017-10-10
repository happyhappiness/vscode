 			fake_av[0] = resolve_refdup("HEAD",
 						    RESOLVE_REF_READING,
 						    oid.hash, NULL);
 			fake_av[1] = NULL;
 			av = fake_av;
 			ac = 1;
+			if (!*av)
+				die("no branches given, and HEAD is not valid");
 		}
 		if (ac != 1)
 			die("--reflog option needs one branch name");
 
 		if (MAX_REVS < reflog)
 			die("Only %d entries can be shown at one time.",
