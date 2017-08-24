{
		add_pax_attr_int(&(pax->pax_header), "size",
		    archive_entry_size(entry_main));
		need_extension = 1;
	}