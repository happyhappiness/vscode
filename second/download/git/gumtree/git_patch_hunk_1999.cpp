 		output(o, 4, _("Merging:"));
 		output_commit_title(o, h1);
 		output_commit_title(o, h2);
 	}
 
 	if (!ca) {
-		ca = get_merge_bases(h1, h2, 1);
+		ca = get_merge_bases(h1, h2);
 		ca = reverse_commit_list(ca);
 	}
 
 	if (show(o, 5)) {
 		unsigned cnt = commit_list_count(ca);
 
