		warning(_("not copying templates from '%s': %s"),
			  template_dir, err.buf);
		strbuf_release(&err);
		goto close_free_return;
	}

	strbuf_addstr(&path, get_git_dir());
	strbuf_complete(&path, '/');
	copy_templates_1(&path, &template_path, dir);
close_free_return:
	closedir(dir);
free_return:
	free(to_free);
