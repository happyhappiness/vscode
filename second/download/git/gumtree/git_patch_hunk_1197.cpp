 		argv_array_push(&store.args, "autostash");
 		argv_array_push(&store.args, "-q");
 		argv_array_push(&store.args, stash_sha1.buf);
 		if (run_command(&store))
 			ret = error(_("cannot store %s"), stash_sha1.buf);
 		else
-			printf(_("Applying autostash resulted in conflicts.\n"
-				"Your changes are safe in the stash.\n"
-				"You can run \"git stash pop\" or"
-				" \"git stash drop\" at any time.\n"));
+			fprintf(stderr,
+				_("Applying autostash resulted in conflicts.\n"
+				  "Your changes are safe in the stash.\n"
+				  "You can run \"git stash pop\" or"
+				  " \"git stash drop\" at any time.\n"));
 	}
 
 	strbuf_release(&stash_sha1);
 	return ret;
 }
 
