 				printf(_("nothing to commit (use -u to show untracked files)\n"));
 			else
 				printf(_("nothing to commit\n"));
 		} else
 			printf(_("nothing to commit, working tree clean\n"));
 	}
+	if(s->show_stash)
+		wt_longstatus_print_stash_summary(s);
 }
 
 static void wt_shortstatus_unmerged(struct string_list_item *it,
 			   struct wt_status *s)
 {
 	struct wt_status_change_data *d = it->util;
