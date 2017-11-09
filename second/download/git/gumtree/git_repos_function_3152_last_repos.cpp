static void handle_filter_error(const struct strbuf *filter_status,
				struct cmd2process *entry,
				const unsigned int wanted_capability) {
	if (!strcmp(filter_status->buf, "error"))
		; /* The filter signaled a problem with the file. */
	else if (!strcmp(filter_status->buf, "abort") && wanted_capability) {
		/*
		 * The filter signaled a permanent problem. Don't try to filter
		 * files with the same command for the lifetime of the current
		 * Git process.
		 */
		 entry->supported_capabilities &= ~wanted_capability;
	} else {
		/*
		 * Something went wrong with the protocol filter.
		 * Force shutdown and restart if another blob requires filtering.
		 */
		error("external filter '%s' failed", entry->subprocess.cmd);
		subprocess_stop(&subprocess_map, &entry->subprocess);
		free(entry);
	}
}