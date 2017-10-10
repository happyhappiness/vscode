 			ac--; av++;
 		}
 		if (all_heads + all_remotes)
 			snarf_refs(all_heads, all_remotes);
 	}
 
-	head_p = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
-				    head_oid.hash, NULL);
-	if (head_p) {
-		head_len = strlen(head_p);
-		memcpy(head, head_p, head_len + 1);
-	}
-	else {
-		head_len = 0;
-		head[0] = 0;
-	}
+	head = resolve_refdup("HEAD", RESOLVE_REF_READING,
+			      head_oid.hash, NULL);
 
-	if (with_current_branch && head_p) {
+	if (with_current_branch && head) {
 		int has_head = 0;
 		for (i = 0; !has_head && i < ref_name_cnt; i++) {
 			/* We are only interested in adding the branch
 			 * HEAD points at.
 			 */
 			if (rev_is_head(head,
-					head_len,
 					ref_name[i],
 					head_oid.hash, NULL))
 				has_head++;
 		}
 		if (!has_head) {
-			int offset = starts_with(head, "refs/heads/") ? 11 : 0;
-			append_one_rev(head + offset);
+			const char *name = head;
+			skip_prefix(name, "refs/heads/", &name);
+			append_one_rev(name);
 		}
 	}
 
 	if (!ref_name_cnt) {
 		fprintf(stderr, "No revs to be shown.\n");
 		exit(0);
