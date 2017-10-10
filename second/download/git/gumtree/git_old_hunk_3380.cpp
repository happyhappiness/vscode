		strbuf_reset(&path);
		strbuf_addstr(&path, git_path("worktrees/%s", d->d_name));
		ret = remove_dir_recursively(&path, 0);
		if (ret < 0 && errno == ENOTDIR)
			ret = unlink(path.buf);
		if (ret)
			error(_("failed to remove: %s"), strerror(errno));
	}
	closedir(dir);
	if (!show_only)
		rmdir(git_path("worktrees"));
	strbuf_release(&reason);
	strbuf_release(&path);
