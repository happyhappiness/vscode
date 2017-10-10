 		    (ce_namelen(ce) <= prefix_length ||
 		     memcmp(prefix, ce->name, prefix_length)))
 			continue;
 		if (last_ce && to_tempfile) {
 			if (ce_namelen(last_ce) != ce_namelen(ce)
 			    || memcmp(last_ce->name, ce->name, ce_namelen(ce)))
-				write_tempfile_record(last_ce->name, prefix_length);
+				write_tempfile_record(last_ce->name, prefix);
 		}
 		if (checkout_entry(ce, &state,
 		    to_tempfile ? topath[ce_stage(ce)] : NULL) < 0)
 			errs++;
 		last_ce = ce;
 	}
 	if (last_ce && to_tempfile)
-		write_tempfile_record(last_ce->name, prefix_length);
+		write_tempfile_record(last_ce->name, prefix);
 	if (errs)
 		/* we have already done our error reporting.
 		 * exit with the same code as die().
 		 */
 		exit(128);
 }
