 	hashclr(result_sha1);
 
 	trace_printf("notes_merge(o->local_ref = %s, o->remote_ref = %s)\n",
 	       o->local_ref, o->remote_ref);
 
 	/* Dereference o->local_ref into local_sha1 */
-	if (read_ref_full(o->local_ref, local_sha1, 0, NULL))
+	if (read_ref_full(o->local_ref, 0, local_sha1, NULL))
 		die("Failed to resolve local notes ref '%s'", o->local_ref);
 	else if (!check_refname_format(o->local_ref, 0) &&
 		is_null_sha1(local_sha1))
 		local = NULL; /* local_sha1 == null_sha1 indicates unborn ref */
 	else if (!(local = lookup_commit_reference(local_sha1)))
 		die("Could not parse local commit %s (%s)",
