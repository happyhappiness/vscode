  */
 static struct worktree *get_main_worktree(void)
 {
 	struct worktree *worktree = NULL;
 	struct strbuf path = STRBUF_INIT;
 	struct strbuf worktree_path = STRBUF_INIT;
-	struct strbuf gitdir = STRBUF_INIT;
 	struct strbuf head_ref = STRBUF_INIT;
 	int is_bare = 0;
 	int is_detached = 0;
 
-	strbuf_addf(&gitdir, "%s", absolute_path(get_git_common_dir()));
-	strbuf_addbuf(&worktree_path, &gitdir);
+	strbuf_addstr(&worktree_path, absolute_path(get_git_common_dir()));
 	is_bare = !strbuf_strip_suffix(&worktree_path, "/.git");
 	if (is_bare)
 		strbuf_strip_suffix(&worktree_path, "/.");
 
 	strbuf_addf(&path, "%s/HEAD", get_git_common_dir());
 
 	if (parse_ref(path.buf, &head_ref, &is_detached) < 0)
 		goto done;
 
 	worktree = xmalloc(sizeof(struct worktree));
 	worktree->path = strbuf_detach(&worktree_path, NULL);
-	worktree->git_dir = strbuf_detach(&gitdir, NULL);
+	worktree->id = NULL;
 	worktree->is_bare = is_bare;
 	worktree->head_ref = NULL;
 	worktree->is_detached = is_detached;
+	worktree->is_current = 0;
 	add_head_info(&head_ref, worktree);
 
 done:
 	strbuf_release(&path);
-	strbuf_release(&gitdir);
 	strbuf_release(&worktree_path);
 	strbuf_release(&head_ref);
 	return worktree;
 }
 
 static struct worktree *get_linked_worktree(const char *id)
 {
 	struct worktree *worktree = NULL;
 	struct strbuf path = STRBUF_INIT;
 	struct strbuf worktree_path = STRBUF_INIT;
-	struct strbuf gitdir = STRBUF_INIT;
 	struct strbuf head_ref = STRBUF_INIT;
 	int is_detached = 0;
 
 	if (!id)
 		die("Missing linked worktree name");
 
-	strbuf_addf(&gitdir, "%s/worktrees/%s",
-			absolute_path(get_git_common_dir()), id);
-	strbuf_addf(&path, "%s/gitdir", gitdir.buf);
+	strbuf_git_common_path(&path, "worktrees/%s/gitdir", id);
 	if (strbuf_read_file(&worktree_path, path.buf, 0) <= 0)
 		/* invalid gitdir file */
 		goto done;
 
 	strbuf_rtrim(&worktree_path);
 	if (!strbuf_strip_suffix(&worktree_path, "/.git")) {
