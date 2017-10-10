			free(entry);
			return 0;
		}
	}
	process = &entry->subprocess.process;

	if (!(wanted_capability & entry->supported_capabilities))
		return 0;

	if (CAP_CLEAN & wanted_capability)
		filter_type = "clean";
	else if (CAP_SMUDGE & wanted_capability)
		filter_type = "smudge";
	else
		die("unexpected filter type");

	sigchain_push(SIGPIPE, SIG_IGN);

