 	}
 	strbuf_release(&buf);
 }
 
 static void record_in_rewritten(struct object_id *oid,
 		enum todo_command next_command) {
-	FILE *out = fopen(rebase_path_rewritten_pending(), "a");
+	FILE *out = fopen_or_warn(rebase_path_rewritten_pending(), "a");
 
 	if (!out)
 		return;
 
 	fprintf(out, "%s\n", oid_to_hex(oid));
 	fclose(out);
