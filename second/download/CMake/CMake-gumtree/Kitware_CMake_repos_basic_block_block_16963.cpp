add_pax_attr_time(&(pax->pax_header),
			    "LIBARCHIVE.creationtime",
			    archive_entry_birthtime(entry_main),
			    archive_entry_birthtime_nsec(entry_main))