 		}
 
 	*olen = len;
 	return name;
 }
 
-static int add_worktree(const char *path, const char **child_argv)
+static int add_worktree(const char *path, const char *refname,
+			const struct add_opts *opts)
 {
 	struct strbuf sb_git = STRBUF_INIT, sb_repo = STRBUF_INIT;
 	struct strbuf sb = STRBUF_INIT;
 	const char *name;
 	struct stat st;
 	struct child_process cp;
+	struct argv_array child_env = ARGV_ARRAY_INIT;
 	int counter = 0, len, ret;
-	unsigned char rev[20];
+	struct strbuf symref = STRBUF_INIT;
+	struct commit *commit = NULL;
 
 	if (file_exists(path) && !is_empty_dir(path))
 		die(_("'%s' already exists"), path);
 
+	/* is 'refname' a branch or commit? */
+	if (opts->force_new_branch) /* definitely a branch */
+		;
+	else if (!opts->detach && !strbuf_check_branch_ref(&symref, refname) &&
+		 ref_exists(symref.buf)) { /* it's a branch */
+		if (!opts->force)
+			die_if_checked_out(symref.buf);
+	} else { /* must be a commit */
+		commit = lookup_commit_reference_by_name(refname);
+		if (!commit)
+			die(_("invalid reference: %s"), refname);
+	}
+
 	name = worktree_basename(path, &len);
 	strbuf_addstr(&sb_repo,
 		      git_path("worktrees/%.*s", (int)(path + len - name), name));
 	len = sb_repo.len;
 	if (safe_create_leading_directories_const(sb_repo.buf))
 		die_errno(_("could not create leading directories of '%s'"),
