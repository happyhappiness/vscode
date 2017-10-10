 	int repeat = opt & OUTPUT_LINE_PORCELAIN;
 	int cnt;
 	const char *cp;
 	struct origin *suspect = ent->suspect;
 	char hex[GIT_SHA1_HEXSZ + 1];
 
-	sha1_to_hex_r(hex, suspect->commit->object.oid.hash);
+	oid_to_hex_r(hex, &suspect->commit->object.oid);
 	printf("%s %d %d %d\n",
 	       hex,
 	       ent->s_lno + 1,
 	       ent->lno + 1,
 	       ent->num_lines);
 	emit_porcelain_details(suspect, repeat);
