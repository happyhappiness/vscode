 	if (!dry_run) {
 		struct string_list refnames = STRING_LIST_INIT_NODUP;
 
 		for (ref = stale_refs; ref; ref = ref->next)
 			string_list_append(&refnames, ref->name);
 
-		result = delete_refs(&refnames);
+		result = delete_refs(&refnames, 0);
 		string_list_clear(&refnames, 0);
 	}
 
 	if (verbosity >= 0) {
 		for (ref = stale_refs; ref; ref = ref->next) {
+			struct strbuf sb = STRBUF_INIT;
 			if (!shown_url) {
 				fprintf(stderr, _("From %.*s\n"), url_len, url);
 				shown_url = 1;
 			}
-			fprintf(stderr, " x %-*s %-*s -> %s\n",
-				TRANSPORT_SUMMARY(_("[deleted]")),
-				REFCOL_WIDTH, _("(none)"), prettify_refname(ref->name));
+			format_display(&sb, '-', _("[deleted]"), NULL,
+				       _("(none)"), prettify_refname(ref->name));
+			fprintf(stderr, " %s\n",sb.buf);
+			strbuf_release(&sb);
 			warn_dangling_symref(stderr, dangling_msg, ref->name);
 		}
 	}
 
 	free(url);
 	free_refs(stale_refs);
