 			commit_list_insert(commit, &complete);
 		}
 	}
 	return 0;
 }
 
+static int mark_complete_oid(const char *refname, const struct object_id *oid,
+			     int flag, void *cb_data)
+{
+	return mark_complete(oid->hash);
+}
+
 static void mark_recent_complete_commits(struct fetch_pack_args *args,
 					 unsigned long cutoff)
 {
 	while (complete && cutoff <= complete->item->date) {
 		if (args->verbose)
 			fprintf(stderr, "Marking %s as complete\n",
