printf(_("%s%s Git repository in %s%s\n"),
		       reinit ? _("Reinitialized existing") : _("Initialized empty"),
		       shared_repository ? _(" shared") : "",
		       git_dir, len && git_dir[len-1] != '/' ? "/" : "");