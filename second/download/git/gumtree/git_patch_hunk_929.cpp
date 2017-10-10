 	rerere(allow_rerere_auto);
 	printf(_("Automatic merge failed; "
 			"fix conflicts and then commit the result.\n"));
 	return 1;
 }
 
-static struct commit *is_old_style_invocation(int argc, const char **argv,
-					      const unsigned char *head)
-{
-	struct commit *second_token = NULL;
-	if (argc > 2) {
-		unsigned char second_sha1[20];
-
-		if (get_sha1(argv[1], second_sha1))
-			return NULL;
-		second_token = lookup_commit_reference_gently(second_sha1, 0);
-		if (!second_token)
-			die(_("'%s' is not a commit"), argv[1]);
-		if (hashcmp(second_token->object.oid.hash, head))
-			return NULL;
-	}
-	return second_token;
-}
-
 static int evaluate_result(void)
 {
 	int cnt = 0;
 	struct rev_info rev;
 
 	/* Check how many files differ. */
