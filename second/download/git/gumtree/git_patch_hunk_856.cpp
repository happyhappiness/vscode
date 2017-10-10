 			   int opt)
 {
 	int repeat = opt & OUTPUT_LINE_PORCELAIN;
 	int cnt;
 	const char *cp;
 	struct origin *suspect = ent->suspect;
-	char hex[GIT_SHA1_HEXSZ + 1];
+	char hex[GIT_MAX_HEXSZ + 1];
 
 	oid_to_hex_r(hex, &suspect->commit->object.oid);
 	printf("%s %d %d %d\n",
 	       hex,
 	       ent->s_lno + 1,
 	       ent->lno + 1,
