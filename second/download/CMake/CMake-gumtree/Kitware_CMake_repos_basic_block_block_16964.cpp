add_pax_attr_time(&(pax->pax_header), "atime",
			    archive_entry_atime(entry_main),
			    archive_entry_atime_nsec(entry_main))