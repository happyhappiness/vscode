		not_found("Not a git repository: '%s'", dir);
	if (!getenv("GIT_HTTP_EXPORT_ALL") &&
	    access("git-daemon-export-ok", F_OK) )
		not_found("Repository not exported: '%s'", dir);

	http_config();
	cmd->imp(cmd_arg);
	return 0;
}
