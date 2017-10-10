 		die("git upload-pack: expected SHA1 list, got '%s'", line);
 	}
 }
 
 static int is_our_ref(struct object *o)
 {
-	return o->flags &
-		((allow_tip_sha1_in_want ? HIDDEN_REF : 0) | OUR_REF);
+	int allow_hidden_ref = (allow_unadvertised_object_request &
+			(ALLOW_TIP_SHA1 | ALLOW_REACHABLE_SHA1));
+	return o->flags & ((allow_hidden_ref ? HIDDEN_REF : 0) | OUR_REF);
 }
 
 static void check_non_tip(void)
 {
 	static const char *argv[] = {
 		"rev-list", "--stdin", NULL,
 	};
 	static struct child_process cmd = CHILD_PROCESS_INIT;
 	struct object *o;
 	char namebuf[42]; /* ^ + SHA-1 + LF */
 	int i;
 
-	/* In the normal in-process case non-tip request can never happen */
-	if (!stateless_rpc)
+	/*
+	 * In the normal in-process case without
+	 * uploadpack.allowReachableSHA1InWant,
+	 * non-tip requests can never happen.
+	 */
+	if (!stateless_rpc && !(allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1))
 		goto error;
 
 	cmd.argv = argv;
 	cmd.git_cmd = 1;
 	cmd.no_stderr = 1;
 	cmd.in = -1;
