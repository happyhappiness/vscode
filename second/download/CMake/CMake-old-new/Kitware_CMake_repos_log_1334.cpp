archive_string_sprintf(&shar->work, "chmod %o ",
		    (unsigned int)(archive_entry_mode(shar->entry) & 07777));