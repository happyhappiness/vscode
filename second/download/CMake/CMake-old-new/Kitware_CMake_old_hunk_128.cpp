
	if (en) {
		/* Everything failed; give up here. */
		archive_set_error(&a->archive, en, "Can't create '%s'",
		    a->name);
		return (ARCHIVE_FAILED);
	}

