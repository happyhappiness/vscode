static int start_multi_file_filter_fn(struct subprocess_entry *subprocess)
{
	static int versions[] = {2, 0};
	static struct subprocess_capability capabilities[] = {
		{ "clean",  CAP_CLEAN  },
		{ "smudge", CAP_SMUDGE },
		{ "delay",  CAP_DELAY  },
		{ NULL, 0 }
	};
	struct cmd2process *entry = (struct cmd2process *)subprocess;
	return subprocess_handshake(subprocess, "git-filter", versions, NULL,
				    capabilities,
				    &entry->supported_capabilities);
}