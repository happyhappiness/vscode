 		remoteheads = collect_parents(head_commit, &head_subsumed, argc, argv);
 		remote_head = remoteheads->item;
 		if (!remote_head)
 			die(_("%s - not something we can merge"), argv[0]);
 		read_empty(remote_head->object.sha1, 0);
 		update_ref("initial pull", "HEAD", remote_head->object.sha1,
-			   NULL, 0, DIE_ON_ERR);
+			   NULL, 0, UPDATE_REFS_DIE_ON_ERR);
 		goto done;
 	} else {
 		struct strbuf merge_names = STRBUF_INIT;
 
 		/* We are invoked directly as the first-class UI. */
 		head_arg = "HEAD";
