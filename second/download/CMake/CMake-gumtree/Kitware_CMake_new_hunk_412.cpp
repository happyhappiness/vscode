
		/* If a length of full-pathname is longer than 240 bytes,
		 * it violates Joliet extensions regulation. */
		if (parent_len > 240
		    || np->mb_len > 240
		    || parent_len + np->mb_len > 240) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "The regulation of Joliet extensions;"
			    " A length of a full-pathname of `%s' is "
