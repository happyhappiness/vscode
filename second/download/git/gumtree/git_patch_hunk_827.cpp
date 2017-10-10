 		/* Register the packfile with core git's machinery. */
 		new_p = add_packed_git(idx_name, strlen(idx_name), 1);
 		if (!new_p)
 			die("core git rejected index %s", idx_name);
 		all_packs[pack_id] = new_p;
 		install_packed_git(new_p);
+		free(idx_name);
 
 		/* Print the boundary */
 		if (pack_edges) {
 			fprintf(pack_edges, "%s:", new_p->pack_name);
 			for (i = 0; i < branch_table_sz; i++) {
 				for (b = branch_table[i]; b; b = b->table_next_branch) {
