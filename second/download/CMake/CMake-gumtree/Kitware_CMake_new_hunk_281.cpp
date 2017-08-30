

	if (en) {

		/* Everything failed; give up here. */

		if ((&a->archive)->error == NULL)

			archive_set_error(&a->archive, en, "Can't create '%s'",

			    a->name);

		return (ARCHIVE_FAILED);

	}



