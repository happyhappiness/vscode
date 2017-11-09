int subprocess_start(struct hashmap *hashmap, struct subprocess_entry *entry, const char *cmd,
	subprocess_start_fn startfn)
{
	int err;
	struct child_process *process;
	const char *argv[] = { cmd, NULL };

	entry->cmd = cmd;
	process = &entry->process;

	child_process_init(process);
	process->argv = argv;
	process->use_shell = 1;
	process->in = -1;
	process->out = -1;
	process->clean_on_exit = 1;
	process->clean_on_exit_handler = subprocess_exit_handler;

	err = start_command(process);
	if (err) {
		error("cannot fork to run subprocess '%s'", cmd);
		return err;
	}

	hashmap_entry_init(entry, strhash(cmd));

	err = startfn(entry);
	if (err) {
		error("initialization for subprocess '%s' failed", cmd);
		subprocess_stop(hashmap, entry);
		return err;
	}

	hashmap_add(hashmap, entry);
	return 0;
}