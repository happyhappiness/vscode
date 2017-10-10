 	const char *agent_feature;
 	int agent_len;
 
 	sort_ref_list(&ref, ref_compare_name);
 	qsort(sought, nr_sought, sizeof(*sought), cmp_ref_by_name);
 
-	if (is_repository_shallow() && !server_supports("shallow"))
+	if ((args->depth > 0 || is_repository_shallow()) && !server_supports("shallow"))
 		die("Server does not support shallow clients");
 	if (server_supports("multi_ack_detailed")) {
 		if (args->verbose)
 			fprintf(stderr, "Server supports multi_ack_detailed\n");
 		multi_ack = 2;
 		if (server_supports("no-done")) {
