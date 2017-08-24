add_pax_attr_time(&(pax->pax_header), "mtime",
			    archive_entry_mtime(entry_main),
			    archive_entry_mtime_nsec(entry_main))