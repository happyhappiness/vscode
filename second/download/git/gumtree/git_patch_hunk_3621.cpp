 			       struct transport *transport,
 			       int check_connectivity)
 {
 	const struct ref *rm = mapped_refs;
 
 	if (check_connectivity) {
-		if (transport->progress)
-			fprintf(stderr, _("Checking connectivity... "));
-		if (check_everything_connected_with_transport(iterate_ref_map,
-							      0, &rm, transport))
+		struct check_connected_options opt = CHECK_CONNECTED_INIT;
+
+		opt.transport = transport;
+		opt.progress = transport->progress;
+
+		if (check_connected(iterate_ref_map, &rm, &opt))
 			die(_("remote did not send all necessary objects"));
-		if (transport->progress)
-			fprintf(stderr, _("done.\n"));
 	}
 
 	if (refs) {
 		write_remote_refs(mapped_refs);
 		if (option_single_branch)
 			write_followtags(refs, msg);
