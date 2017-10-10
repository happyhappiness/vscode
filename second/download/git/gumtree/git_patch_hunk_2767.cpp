 		die(_("Ambiguous object name: '%s'."), start_name);
 		break;
 	}
 
 	if ((commit = lookup_commit_reference(sha1)) == NULL)
 		die(_("Not a valid branch point: '%s'."), start_name);
-	hashcpy(sha1, commit->object.sha1);
+	hashcpy(sha1, commit->object.oid.hash);
 
 	if (forcing)
 		snprintf(msg, sizeof msg, "branch: Reset to %s",
 			 start_name);
 	else if (!dont_change_ref)
 		snprintf(msg, sizeof msg, "branch: Created from %s",
