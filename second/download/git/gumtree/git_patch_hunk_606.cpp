 	if (wt->is_bare)
 		printf("bare\n");
 	else {
 		printf("HEAD %s\n", sha1_to_hex(wt->head_sha1));
 		if (wt->is_detached)
 			printf("detached\n");
-		else
+		else if (wt->head_ref)
 			printf("branch %s\n", wt->head_ref);
 	}
 	printf("\n");
 }
 
 static void show_worktree(struct worktree *wt, int path_maxlen, int abbrev_len)
