{
		/*
		 * If rdevmajor is too large, add 'SCHILY.devmajor' to
		 * extended attributes.
		 */
		int rdevmajor, rdevminor;
		rdevmajor = archive_entry_rdevmajor(entry_main);
		rdevminor = archive_entry_rdevminor(entry_main);
		if (rdevmajor >= (1 << 18)) {
			add_pax_attr_int(&(pax->pax_header), "SCHILY.devmajor",
			    rdevmajor);
			/*
			 * Non-strict formatting below means we don't
			 * have to truncate here.  Not truncating improves
			 * the chance that some more modern tar archivers
			 * (such as GNU tar 1.13) can restore the full
			 * value even if they don't understand the pax
			 * extended attributes.  See my rant below about
			 * file size fields for additional details.
			 */
			/* archive_entry_set_rdevmajor(entry_main,
			   rdevmajor & ((1 << 18) - 1)); */
			need_extension = 1;
		}

		/*
		 * If devminor is too large, add 'SCHILY.devminor' to
		 * extended attributes.
		 */
		if (rdevminor >= (1 << 18)) {
			add_pax_attr_int(&(pax->pax_header), "SCHILY.devminor",
			    rdevminor);
			/* Truncation is not necessary here, either. */
			/* archive_entry_set_rdevminor(entry_main,
			   rdevminor & ((1 << 18) - 1)); */
			need_extension = 1;
		}
	}