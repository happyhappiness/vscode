		not_found("Not a git repository: '%s'", dir);
	if (!getenv("GIT_HTTP_EXPORT_ALL") &&
	    access("git-daemon-export-ok", F_OK) )
		not_found("Repository not exported: '%s'", dir);

	http_config();
	max_request_buffer = git_env_ulong("GIT_HTTP_MAX_REQUEST_BUFFER",
					   max_request_buffer);

	cmd->imp(cmd_arg);
	return 0;
}
