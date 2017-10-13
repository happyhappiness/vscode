printf(_("%s%s Git repository in %s%s\n"),
		       reinit ? _("Reinitialized existing") : _("Initialized empty"),
		       get_shared_repository() ? _(" shared") : "",
		       git_dir, len && git_dir[len-1] != '/' ? "/" : "");