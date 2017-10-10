
		/* TRANSLATORS: The first '%s' is either "Reinitialized
		   existing" or "Initialized empty", the second " shared" or
		   "", and the last '%s%s' is the verbatim directory name. */
		printf(_("%s%s Git repository in %s%s\n"),
		       reinit ? _("Reinitialized existing") : _("Initialized empty"),
		       get_shared_repository() ? _(" shared") : "",
		       git_dir, len && git_dir[len-1] != '/' ? "/" : "");
	}

	return 0;
}

