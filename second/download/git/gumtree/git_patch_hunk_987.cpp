 		if (!prune_worktree(d->d_name, &reason))
 			continue;
 		if (show_only || verbose)
 			printf("%s\n", reason.buf);
 		if (show_only)
 			continue;
-		strbuf_reset(&path);
-		strbuf_addstr(&path, git_path("worktrees/%s", d->d_name));
+		git_path_buf(&path, "worktrees/%s", d->d_name);
 		ret = remove_dir_recursively(&path, 0);
 		if (ret < 0 && errno == ENOTDIR)
 			ret = unlink(path.buf);
 		if (ret)
 			error_errno(_("failed to remove '%s'"), path.buf);
 	}
