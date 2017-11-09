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