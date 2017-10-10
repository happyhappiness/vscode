 		strbuf_addstr(&sb, "(bare)");
 	else {
 		strbuf_addf(&sb, "%-*s ", abbrev_len,
 				find_unique_abbrev(wt->head_sha1, DEFAULT_ABBREV));
 		if (wt->is_detached)
 			strbuf_addstr(&sb, "(detached HEAD)");
-		else if (wt->head_ref)
-			strbuf_addf(&sb, "[%s]", shorten_unambiguous_ref(wt->head_ref, 0));
-		else
+		else if (wt->head_ref) {
+			char *ref = shorten_unambiguous_ref(wt->head_ref, 0);
+			strbuf_addf(&sb, "[%s]", ref);
+			free(ref);
+		} else
 			strbuf_addstr(&sb, "(error)");
 	}
 	printf("%s\n", sb.buf);
 
 	strbuf_release(&sb);
 }
