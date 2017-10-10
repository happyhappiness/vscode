			free(entry);
			return 0;
		}
	}
	process = &entry->subprocess.process;

	if (!(entry->supported_capabilities & wanted_capability))
		return 0;

	if (wanted_capability & CAP_CLEAN)
		filter_type = "clean";
	else if (wanted_capability & CAP_SMUDGE)
		filter_type = "smudge";
	else
		die("unexpected filter type");

	sigchain_push(SIGPIPE, SIG_IGN);

