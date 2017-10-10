 			fprintf(stderr, "    sending %d objects\n",
 				objects_to_send);
 
 		run_request_queue();
 
 		/* Update the remote branch if all went well */
-		if (aborted || !update_remote(ref->new_sha1, ref_lock))
+		if (aborted || !update_remote(ref->new_oid.hash, ref_lock))
 			rc = 1;
 
 		if (!rc)
 			fprintf(stderr, "    done\n");
 		if (helper_status)
 			printf("%s %s\n", !rc ? "ok" : "error", ref->name);
 		unlock_remote(ref_lock);
 		check_locks();
+		argv_array_clear(&commit_argv);
 	}
 
 	/* Update remote server info if appropriate */
 	if (repo->has_info_refs && new_refs) {
 		if (info_ref_lock && repo->can_update_info_refs) {
 			fprintf(stderr, "Updating remote server info\n");
