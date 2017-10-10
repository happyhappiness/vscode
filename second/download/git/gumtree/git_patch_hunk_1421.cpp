  * created, and is not meant to flip between different work trees.
  */
 void set_git_work_tree(const char *new_work_tree)
 {
 	if (git_work_tree_initialized) {
 		new_work_tree = real_path(new_work_tree);
-		if (strcmp(new_work_tree, work_tree))
+		if (strcmp(new_work_tree, the_repository->worktree))
 			die("internal error: work tree has already been set\n"
 			    "Current worktree: %s\nNew worktree: %s",
-			    work_tree, new_work_tree);
+			    the_repository->worktree, new_work_tree);
 		return;
 	}
 	git_work_tree_initialized = 1;
-	work_tree = real_pathdup(new_work_tree, 1);
+	repo_set_worktree(the_repository, new_work_tree);
 }
 
 const char *get_git_work_tree(void)
 {
-	return work_tree;
+	return the_repository->worktree;
 }
 
 char *get_object_directory(void)
 {
-	if (!git_object_dir)
-		setup_git_env();
-	return git_object_dir;
+	if (!the_repository->objectdir)
+		BUG("git environment hasn't been setup");
+	return the_repository->objectdir;
 }
 
 int odb_mkstemp(struct strbuf *template, const char *pattern)
 {
 	int fd;
 	/*
