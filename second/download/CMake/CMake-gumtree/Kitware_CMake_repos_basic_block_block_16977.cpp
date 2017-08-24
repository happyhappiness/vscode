{
		add_pax_attr_int(&(pax->pax_header), "uid",
		    archive_entry_uid(entry_main));
		need_extension = 1;
	}