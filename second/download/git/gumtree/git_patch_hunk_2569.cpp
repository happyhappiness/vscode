 
 static const char * const verify_commit_usage[] = {
 		N_("git verify-commit [-v | --verbose] <commit>..."),
 		NULL
 };
 
-static int run_gpg_verify(const unsigned char *sha1, const char *buf, unsigned long size, int verbose)
+static int run_gpg_verify(const unsigned char *sha1, const char *buf, unsigned long size, unsigned flags)
 {
 	struct signature_check signature_check;
+	int ret;
 
 	memset(&signature_check, 0, sizeof(signature_check));
 
-	check_commit_signature(lookup_commit(sha1), &signature_check);
-
-	if (verbose && signature_check.payload)
-		fputs(signature_check.payload, stdout);
-
-	if (signature_check.gpg_output)
-		fputs(signature_check.gpg_output, stderr);
+	ret = check_commit_signature(lookup_commit(sha1), &signature_check);
+	print_signature_buffer(&signature_check, flags);
 
 	signature_check_clear(&signature_check);
-	return signature_check.result != 'G';
+	return ret;
 }
 
-static int verify_commit(const char *name, int verbose)
+static int verify_commit(const char *name, unsigned flags)
 {
 	enum object_type type;
 	unsigned char sha1[20];
 	char *buf;
 	unsigned long size;
 	int ret;
