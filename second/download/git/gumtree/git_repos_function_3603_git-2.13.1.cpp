static int push_submodule(const char *path,
			  const struct remote *remote,
			  const char **refspec, int refspec_nr,
			  const struct string_list *push_options,
			  int dry_run)
{
	if (add_submodule_odb(path))
		return 1;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		argv_array_push(&cp.args, "push");
		if (dry_run)
			argv_array_push(&cp.args, "--dry-run");

		if (push_options && push_options->nr) {
			const struct string_list_item *item;
			for_each_string_list_item(item, push_options)
				argv_array_pushf(&cp.args, "--push-option=%s",
						 item->string);
		}

		if (remote->origin != REMOTE_UNCONFIGURED) {
			int i;
			argv_array_push(&cp.args, remote->name);
			for (i = 0; i < refspec_nr; i++)
				argv_array_push(&cp.args, refspec[i]);
		}

		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.dir = path;
		if (run_command(&cp))
			return 0;
		close(cp.out);
	}

	return 1;
}