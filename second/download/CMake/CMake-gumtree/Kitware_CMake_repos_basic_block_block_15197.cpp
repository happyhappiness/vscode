(en) {
		/* Everything failed; give up here. */
		archive_set_error(&a->archive, en, "Can't create '%ls'",
		    a->name);
		return (ARCHIVE_FAILED);
	}