 	errno = 0;
 	ul = strtoul(arg, &endp, 8);
 	if (errno || endp == arg || *endp != ',' || (unsigned int) ul != ul)
 		return -1; /* not a new-style cacheinfo */
 	*mode = ul;
 	endp++;
-	if (get_sha1_hex(endp, sha1) || endp[40] != ',')
+	if (get_oid_hex(endp, oid) || endp[GIT_SHA1_HEXSZ] != ',')
 		return -1;
-	*path = endp + 41;
+	*path = endp + GIT_SHA1_HEXSZ + 1;
 	return 0;
 }
 
 static int cacheinfo_callback(struct parse_opt_ctx_t *ctx,
 				const struct option *opt, int unset)
 {
-	unsigned char sha1[20];
+	struct object_id oid;
 	unsigned int mode;
 	const char *path;
 
-	if (!parse_new_style_cacheinfo(ctx->argv[1], &mode, sha1, &path)) {
-		if (add_cacheinfo(mode, sha1, path, 0))
+	if (!parse_new_style_cacheinfo(ctx->argv[1], &mode, &oid, &path)) {
+		if (add_cacheinfo(mode, &oid, path, 0))
 			die("git update-index: --cacheinfo cannot add %s", path);
 		ctx->argv++;
 		ctx->argc--;
 		return 0;
 	}
 	if (ctx->argc <= 3)
 		return error("option 'cacheinfo' expects <mode>,<sha1>,<path>");
 	if (strtoul_ui(*++ctx->argv, 8, &mode) ||
-	    get_sha1_hex(*++ctx->argv, sha1) ||
-	    add_cacheinfo(mode, sha1, *++ctx->argv, 0))
+	    get_oid_hex(*++ctx->argv, &oid) ||
+	    add_cacheinfo(mode, &oid, *++ctx->argv, 0))
 		die("git update-index: --cacheinfo cannot add %s", *ctx->argv);
 	ctx->argc -= 3;
 	return 0;
 }
 
 static int stdin_cacheinfo_callback(struct parse_opt_ctx_t *ctx,
