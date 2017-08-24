{
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