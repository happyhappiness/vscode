		goto done;

	err = subprocess_read_status(process->out, &filter_status);
	if (err)
		goto done;

	err = strcmp(filter_status.buf, "success");
	if (err)
		goto done;

	err = read_packetized_to_strbuf(process->out, &nbuf) < 0;
	if (err)
		goto done;

	err = subprocess_read_status(process->out, &filter_status);
	if (err)
		goto done;

	err = strcmp(filter_status.buf, "success");

done:
	sigchain_pop(SIGPIPE);

	if (err) {
		if (!strcmp(filter_status.buf, "error")) {
			/* The filter signaled a problem with the file. */
		} else if (!strcmp(filter_status.buf, "abort")) {
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
			error("external filter '%s' failed", cmd);
			subprocess_stop(&subprocess_map, &entry->subprocess);
			free(entry);
		}
	} else {
		strbuf_swap(dst, &nbuf);
	}
	strbuf_release(&nbuf);
	return !err;
}

static struct convert_driver {
	const char *name;
	struct convert_driver *next;
