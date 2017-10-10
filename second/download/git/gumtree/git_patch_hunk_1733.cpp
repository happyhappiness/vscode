 		/*
 		 * There is no unmerged entry, don't advise 'git
 		 * add/rm <file>', just 'git commit'.
 		 */
 		if (advice_resolve_conflict)
 			die(_("You have not concluded your merge (MERGE_HEAD exists).\n"
-				  "Please, commit your changes before you can merge."));
+				  "Please, commit your changes before you merge."));
 		else
 			die(_("You have not concluded your merge (MERGE_HEAD exists)."));
 	}
 	if (file_exists(git_path("CHERRY_PICK_HEAD"))) {
 		if (advice_resolve_conflict)
 			die(_("You have not concluded your cherry-pick (CHERRY_PICK_HEAD exists).\n"
-			    "Please, commit your changes before you can merge."));
+			    "Please, commit your changes before you merge."));
 		else
 			die(_("You have not concluded your cherry-pick (CHERRY_PICK_HEAD exists)."));
 	}
 	resolve_undo_clear();
 
 	if (verbosity < 0)
