static int handshake_capabilities(struct child_process *process,
				  struct subprocess_capability *capabilities,
				  unsigned int *supported_capabilities)
{
	int i;
	char *line;

	for (i = 0; capabilities[i].name; i++) {
		if (packet_write_fmt_gently(process->in, "capability=%s\n",
					    capabilities[i].name))
			return error("Could not write requested capability");
	}
	if (packet_flush_gently(process->in))
		return error("Could not write flush packet");

	while ((line = packet_read_line(process->out, NULL))) {
		const char *p;
		if (!skip_prefix(line, "capability=", &p))
			continue;

		for (i = 0;
		     capabilities[i].name && strcmp(p, capabilities[i].name);
		     i++)
			;
		if (capabilities[i].name) {
			if (supported_capabilities)
				*supported_capabilities |= capabilities[i].flag;
		} else {
			warning("subprocess '%s' requested unsupported capability '%s'",
				process->argv[0], p);
		}
	}

	return 0;
}