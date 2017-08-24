(linkpath_length > 100 || has_non_ASCII(linkpath)) {
			add_pax_attr(&(pax->pax_header), "linkpath", linkpath);
			if (linkpath_length > 100) {
				if (hardlink != NULL)
					archive_entry_set_hardlink(entry_main,
					    "././@LongHardLink");
				else
					archive_entry_set_symlink(entry_main,
					    "././@LongSymLink");
			}
			need_extension = 1;
		}