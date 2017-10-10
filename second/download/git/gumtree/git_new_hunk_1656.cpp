		return err;
	}

	hashmap_add(hashmap, entry);
	return 0;
}

static int handshake_version(struct child_process *process,
			     const char *welcome_prefix, int *versions,
			     int *chosen_version)
{
	int version_scratch;
	int i;
	char *line;
	const char *p;

	if (!chosen_version)
		chosen_version = &version_scratch;

	if (packet_write_fmt_gently(process->in, "%s-client\n",
				    welcome_prefix))
		return error("Could not write client identification");
	for (i = 0; versions[i]; i++) {
		if (packet_write_fmt_gently(process->in, "version=%d\n",
					    versions[i]))
			return error("Could not write requested version");
	}
	if (packet_flush_gently(process->in))
		return error("Could not write flush packet");

	if (!(line = packet_read_line(process->out, NULL)) ||
	    !skip_prefix(line, welcome_prefix, &p) ||
	    strcmp(p, "-server"))
		return error("Unexpected line '%s', expected %s-server",
			     line ? line : "<flush packet>", welcome_prefix);
	if (!(line = packet_read_line(process->out, NULL)) ||
	    !skip_prefix(line, "version=", &p) ||
	    strtol_i(p, 10, chosen_version))
		return error("Unexpected line '%s', expected version",
			     line ? line : "<flush packet>");
	if ((line = packet_read_line(process->out, NULL)))
		return error("Unexpected line '%s', expected flush", line);

	/* Check to make sure that the version received is supported */
	for (i = 0; versions[i]; i++) {
		if (versions[i] == *chosen_version)
			break;
	}
	if (!versions[i])
		return error("Version %d not supported", *chosen_version);

	return 0;
}

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

int subprocess_handshake(struct subprocess_entry *entry,
			 const char *welcome_prefix,
			 int *versions,
			 int *chosen_version,
			 struct subprocess_capability *capabilities,
			 unsigned int *supported_capabilities)
{
	int retval;
	struct child_process *process = &entry->process;

	sigchain_push(SIGPIPE, SIG_IGN);

	retval = handshake_version(process, welcome_prefix, versions,
				   chosen_version) ||
		 handshake_capabilities(process, capabilities,
					supported_capabilities);

	sigchain_pop(SIGPIPE);
	return retval;
}
