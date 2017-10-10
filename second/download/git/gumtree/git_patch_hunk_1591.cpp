 		free(worktrees[i]->lock_reason);
 		free(worktrees[i]);
 	}
 	free (worktrees);
 }
 
-/*
- * read 'path_to_ref' into 'ref'.  Also if is_detached is not NULL,
- * set is_detached to 1 (0) if the ref is detached (is not detached).
- *
- * $GIT_COMMON_DIR/$symref (e.g. HEAD) is practically outside $GIT_DIR so
- * for linked worktrees, `resolve_ref_unsafe()` won't work (it uses
- * git_path). Parse the ref ourselves.
- *
- * return -1 if the ref is not a proper ref, 0 otherwise (success)
- */
-static int parse_ref(char *path_to_ref, struct strbuf *ref, int *is_detached)
-{
-	if (is_detached)
-		*is_detached = 0;
-	if (!strbuf_readlink(ref, path_to_ref, 0)) {
-		/* HEAD is symbolic link */
-		if (!starts_with(ref->buf, "refs/") ||
-				check_refname_format(ref->buf, 0))
-			return -1;
-	} else if (strbuf_read_file(ref, path_to_ref, 0) >= 0) {
-		/* textual symref or detached */
-		if (!starts_with(ref->buf, "ref:")) {
-			if (is_detached)
-				*is_detached = 1;
-		} else {
-			strbuf_remove(ref, 0, strlen("ref:"));
-			strbuf_trim(ref);
-			if (check_refname_format(ref->buf, 0))
-				return -1;
-		}
-	} else
-		return -1;
-	return 0;
-}
-
 /**
- * Add the head_sha1 and head_ref (if not detached) to the given worktree
+ * Update head_sha1, head_ref and is_detached of the given worktree
  */
-static void add_head_info(struct strbuf *head_ref, struct worktree *worktree)
+static void add_head_info(struct worktree *wt)
 {
-	if (head_ref->len) {
-		if (worktree->is_detached) {
-			get_sha1_hex(head_ref->buf, worktree->head_sha1);
-		} else {
-			resolve_ref_unsafe(head_ref->buf, 0, worktree->head_sha1, NULL);
-			worktree->head_ref = strbuf_detach(head_ref, NULL);
-		}
-	}
+	int flags;
+	const char *target;
+
+	target = refs_resolve_ref_unsafe(get_worktree_ref_store(wt),
+					 "HEAD",
+					 RESOLVE_REF_READING,
+					 wt->head_sha1, &flags);
+	if (!target)
+		return;
+
+	if (flags & REF_ISSYMREF)
+		wt->head_ref = xstrdup(target);
+	else
+		wt->is_detached = 1;
 }
 
 /**
  * get the main worktree
  */
 static struct worktree *get_main_worktree(void)
 {
 	struct worktree *worktree = NULL;
 	struct strbuf path = STRBUF_INIT;
 	struct strbuf worktree_path = STRBUF_INIT;
-	struct strbuf head_ref = STRBUF_INIT;
 	int is_bare = 0;
-	int is_detached = 0;
 
 	strbuf_add_absolute_path(&worktree_path, get_git_common_dir());
 	is_bare = !strbuf_strip_suffix(&worktree_path, "/.git");
 	if (is_bare)
 		strbuf_strip_suffix(&worktree_path, "/.");
 
 	strbuf_addf(&path, "%s/HEAD", get_git_common_dir());
 
 	worktree = xcalloc(1, sizeof(*worktree));
 	worktree->path = strbuf_detach(&worktree_path, NULL);
 	worktree->is_bare = is_bare;
-	worktree->is_detached = is_detached;
-	if (!parse_ref(path.buf, &head_ref, &is_detached))
-		add_head_info(&head_ref, worktree);
+	add_head_info(worktree);
 
 	strbuf_release(&path);
 	strbuf_release(&worktree_path);
-	strbuf_release(&head_ref);
 	return worktree;
 }
 
 static struct worktree *get_linked_worktree(const char *id)
 {
 	struct worktree *worktree = NULL;
 	struct strbuf path = STRBUF_INIT;
 	struct strbuf worktree_path = STRBUF_INIT;
-	struct strbuf head_ref = STRBUF_INIT;
-	int is_detached = 0;
 
 	if (!id)
 		die("Missing linked worktree name");
 
-	strbuf_git_common_path(&path, "worktrees/%s/gitdir", id);
+	strbuf_git_common_path(&path, the_repository, "worktrees/%s/gitdir", id);
 	if (strbuf_read_file(&worktree_path, path.buf, 0) <= 0)
 		/* invalid gitdir file */
 		goto done;
 
 	strbuf_rtrim(&worktree_path);
 	if (!strbuf_strip_suffix(&worktree_path, "/.git")) {
