{
		add_pax_attr_int(&(pax->pax_header), "gid",
		    archive_entry_gid(entry_main));
		need_extension = 1;
	}