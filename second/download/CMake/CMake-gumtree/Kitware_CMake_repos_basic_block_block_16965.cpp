add_pax_attr_time(&(pax->pax_header), "ctime",
			    archive_entry_ctime(entry_main),
			    archive_entry_ctime_nsec(entry_main))