 	int cnt;
 	const char *cp;
 	struct origin *suspect = ent->suspect;
 	char hex[41];
 
 	strcpy(hex, sha1_to_hex(suspect->commit->object.sha1));
-	printf("%s%c%d %d %d\n",
+	printf("%s %d %d %d\n",
 	       hex,
-	       ent->guilty ? ' ' : '*', /* purely for debugging */
 	       ent->s_lno + 1,
 	       ent->lno + 1,
 	       ent->num_lines);
 	emit_porcelain_details(suspect, repeat);
 
 	cp = nth_line(sb, ent->lno);
