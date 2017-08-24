{
			/*
			 * We don't know if it's pax: If the bid
			 * function sees a valid ustar header
			 * immediately following, then let's ignore
			 * the hardlink size.
			 */
			archive_entry_set_size(entry, 0);
			tar->entry_bytes_remaining = 0;
		}