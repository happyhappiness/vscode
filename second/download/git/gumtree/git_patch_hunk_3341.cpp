 		}
 	}
 
 	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
 		die(_("unable to write new index file"));
 
-	read_ref_full("HEAD", 0, rev, &flag);
+	read_ref_full("HEAD", 0, rev, NULL);
 	head = lookup_commit_reference_gently(rev, 1);
 
 	errs |= post_checkout_hook(head, head, 0);
 	return errs;
 }
 
