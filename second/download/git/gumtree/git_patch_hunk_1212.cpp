 			dont_change_ref = 1;
 		else
 			forcing = 1;
 	}
 
 	real_ref = NULL;
-	if (get_sha1(start_name, sha1)) {
+	if (get_oid(start_name, &oid)) {
 		if (explicit_tracking) {
 			if (advice_set_upstream_failure) {
 				error(_(upstream_missing), start_name);
 				advise(_(upstream_advice));
 				exit(1);
 			}
 			die(_(upstream_missing), start_name);
 		}
 		die(_("Not a valid object name: '%s'."), start_name);
 	}
 
-	switch (dwim_ref(start_name, strlen(start_name), sha1, &real_ref)) {
+	switch (dwim_ref(start_name, strlen(start_name), oid.hash, &real_ref)) {
 	case 0:
 		/* Not branching from any existing branch */
 		if (explicit_tracking)
 			die(_(upstream_not_branch), start_name);
 		break;
 	case 1:
