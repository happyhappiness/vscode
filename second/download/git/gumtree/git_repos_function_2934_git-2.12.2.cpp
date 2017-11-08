static void kill_multi_file_filter(struct hashmap *hashmap, struct cmd2process *entry)
{
	if (!entry)
		return;

	entry->process.clean_on_exit = 0;
	kill(entry->process.pid, SIGTERM);
	finish_command(&entry->process);

	hashmap_remove(hashmap, entry, NULL);
	free(entry);
}