 {
 	struct ref *posn;
 	for (posn = refs; posn; posn = posn->next) {
 		if (posn->symref)
 			printf("@%s %s\n", posn->symref, posn->name);
 		else
-			printf("%s %s\n", sha1_to_hex(posn->old_sha1), posn->name);
+			printf("%s %s\n", oid_to_hex(&posn->old_oid), posn->name);
 	}
 	printf("\n");
 	fflush(stdout);
 }
 
 struct rpc_state {
