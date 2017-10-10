		warning(_("templates not found %s"), template_dir);
		goto free_return;
	}

	/* Make sure that template is from the correct vintage */
	strbuf_addstr(&template_path, "config");
	read_repository_format(&template_format, template_path.buf);
	strbuf_setlen(&template_path, template_len);

	/*
	 * No mention of version at all is OK, but anything else should be
	 * verified.
	 */
	if (template_format.version >= 0 &&
	    verify_repository_format(&template_format, &err) < 0) {
		warning(_("not copying templates from '%s': %s"),
			  template_dir, err.buf);
		strbuf_release(&err);
		goto close_free_return;
	}

	strbuf_addstr(&path, get_git_dir());
	strbuf_complete(&path, '/');
	copy_templates_1(&path, &template_path, dir);
