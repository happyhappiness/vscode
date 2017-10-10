 		 * Reset the hook args to tell the real story.
 		 */
 		hook_arg1 = "message";
 		hook_arg2 = "";
 	}
 
-	s->fp = fopen(git_path(commit_editmsg), "w");
+	s->fp = fopen_for_writing(git_path(commit_editmsg));
 	if (s->fp == NULL)
 		die_errno(_("could not open '%s'"), git_path(commit_editmsg));
 
 	/* Ignore status.displayCommentPrefix: we do need comments in COMMIT_EDITMSG. */
 	old_display_comment_prefix = s->display_comment_prefix;
 	s->display_comment_prefix = 1;
