 				fprintf(stderr, "  git remote set-head %s %s\n",
 					argv[0], states.heads.items[i].string);
 		} else
 			head_name = xstrdup(states.heads.items[0].string);
 		free_remote_ref_states(&states);
 	} else if (opt_d && !opt_a && argc == 1) {
-		if (delete_ref(buf.buf, NULL, REF_NODEREF))
+		if (delete_ref(NULL, buf.buf, NULL, REF_NODEREF))
 			result |= error(_("Could not delete %s"), buf.buf);
 	} else
 		usage_with_options(builtin_remote_sethead_usage, options);
 
 	if (head_name) {
 		strbuf_addf(&buf2, "refs/remotes/%s/%s", argv[0], head_name);
