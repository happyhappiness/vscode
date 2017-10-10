 		lost,
 		sb.buf);
 	strbuf_release(&sb);
 
 	if (advice_detached_head)
 		fprintf(stderr,
-			_(
+			Q_(
+			/* The singular version */
+			"If you want to keep it by creating a new branch, "
+			"this may be a good time\nto do so with:\n\n"
+			" git branch <new-branch-name> %s\n\n",
+			/* The plural version */
 			"If you want to keep them by creating a new branch, "
 			"this may be a good time\nto do so with:\n\n"
-			" git branch <new-branch-name> %s\n\n"),
+			" git branch <new-branch-name> %s\n\n",
+			/* Give ngettext() the count */
+			lost),
 			find_unique_abbrev(commit->object.sha1, DEFAULT_ABBREV));
 }
 
 /*
  * We are about to leave commit that was at the tip of a detached
  * HEAD.  If it is not reachable from any ref, this is the last chance
