 	return 0;
 }
 
 static int verify_tag(const char *name, const char *ref,
 				const unsigned char *sha1)
 {
-	const char *argv_verify_tag[] = {"verify-tag",
-					"-v", "SHA1_HEX", NULL};
-	argv_verify_tag[2] = sha1_to_hex(sha1);
-
-	if (run_command_v_opt(argv_verify_tag, RUN_GIT_CMD))
-		return error(_("could not verify the tag '%s'"), name);
-	return 0;
+	return gpg_verify_tag(sha1, name, GPG_VERIFY_VERBOSE);
 }
 
 static int do_sign(struct strbuf *buffer)
 {
 	return sign_buffer(buffer, buffer, get_signing_key());
 }
