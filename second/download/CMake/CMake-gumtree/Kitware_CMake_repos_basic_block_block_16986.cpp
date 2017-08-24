{
				add_pax_attr(&(pax->pax_header), "path", path);
				archive_entry_set_pathname(entry_main,
				    build_ustar_entry_name(ustar_entry_name,
					path, path_length, NULL));
				need_extension = 1;
			}