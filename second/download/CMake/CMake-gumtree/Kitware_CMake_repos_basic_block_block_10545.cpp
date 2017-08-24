{
			/* If there is no symname, handle it as a regular
			 * file. */
			zip_entry->mode &= ~AE_IFMT;
			zip_entry->mode |= AE_IFREG;
			archive_entry_set_mode(entry, zip_entry->mode);
		}