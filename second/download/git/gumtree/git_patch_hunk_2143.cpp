 					opt.pattern_list->pattern);
 			string_list_append(&path_list, buf.buf);
 			strbuf_detach(&buf, NULL);
 		}
 	}
 
-	if (!show_in_pager)
+	if (!show_in_pager && !opt.status_only)
 		setup_pager();
 
 	if (!use_index && (untracked || cached))
 		die(_("--cached or --untracked cannot be used with --no-index."));
 
 	if (!use_index || untracked) {
