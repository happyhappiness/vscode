 				errs |= checkout_stage(opts->writeout_stage, ce, pos, &state);
 			else if (opts->merge)
 				errs |= checkout_merged(pos, &state);
 			pos = skip_same_name(ce, pos) - 1;
 		}
 	}
+	errs |= finish_delayed_checkout(&state);
 
 	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
 		die(_("unable to write new index file"));
 
 	read_ref_full("HEAD", 0, rev.hash, NULL);
 	head = lookup_commit_reference_gently(&rev, 1);
