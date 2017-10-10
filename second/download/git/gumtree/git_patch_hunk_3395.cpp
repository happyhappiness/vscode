 		if (new_pack && find_pack_entry_one(sha1, new_pack))
 			continue;
 
 		memcpy(commit, sha1_to_hex(sha1), 40);
 		if (write_in_full(rev_list.in, commit, 41) < 0) {
 			if (errno != EPIPE && errno != EINVAL)
-				error(_("failed write to rev-list: %s"),
-				      strerror(errno));
+				error_errno(_("failed write to rev-list"));
 			err = -1;
 			break;
 		}
 	} while (!fn(cb_data, sha1));
 
-	if (close(rev_list.in)) {
-		error(_("failed to close rev-list's stdin: %s"), strerror(errno));
-		err = -1;
-	}
+	if (close(rev_list.in))
+		err = error_errno(_("failed to close rev-list's stdin"));
 
 	sigchain_pop(SIGPIPE);
 	return finish_command(&rev_list) || err;
 }
 
 int check_everything_connected_with_transport(sha1_iterate_fn fn,
