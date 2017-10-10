		else if (value && !strcasecmp(value, "crlf"))
			core_eol = EOL_CRLF;
		else if (value && !strcasecmp(value, "native"))
			core_eol = EOL_NATIVE;
		else
			core_eol = EOL_UNSET;
		return 0;
	}

	if (!strcmp(var, "core.notesref")) {
		notes_ref_name = xstrdup(value);
		return 0;
