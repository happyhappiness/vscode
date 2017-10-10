 			info.header_prefix = "commit ";
 	}
 	else if (revs.verbose_header)
 		/* Only --header was specified */
 		revs.commit_format = CMIT_FMT_RAW;
 
-	if ((!revs.commits &&
+	if ((!revs.commits && reflog_walk_empty(revs.reflog_info) &&
 	     (!(revs.tag_objects || revs.tree_objects || revs.blob_objects) &&
-	      !revs.pending.nr)) ||
+	      !revs.pending.nr) &&
+	     !revs.rev_input_given) ||
 	    revs.diff)
 		usage(rev_list_usage);
 
 	if (revs.show_notes)
 		die(_("rev-list does not support display of notes"));
 
