 
 	memcpy(&opts, &rev->diffopt, sizeof(opts));
 	opts.output_format = DIFF_FORMAT_SUMMARY | DIFF_FORMAT_DIFFSTAT;
 
 	diff_setup_done(&opts);
 
-	diff_tree_sha1(origin->tree->object.oid.hash,
-		       head->tree->object.oid.hash,
-		       "", &opts);
+	diff_tree_oid(&origin->tree->object.oid,
+		      &head->tree->object.oid,
+		      "", &opts);
 	diffcore_std(&opts);
 	diff_flush(&opts);
 
 	fprintf(rev->diffopt.file, "\n");
 }
 
