 	diff_tree_sha1(origin->tree->object.oid.hash,
 		       head->tree->object.oid.hash,
 		       "", &opts);
 	diffcore_std(&opts);
 	diff_flush(&opts);
 
-	printf("\n");
-	print_signature();
+	fprintf(rev->diffopt.file, "\n");
+	print_signature(rev->diffopt.file);
 }
 
 static const char *clean_message_id(const char *msg_id)
 {
 	char ch;
 	const char *a, *z, *m;
