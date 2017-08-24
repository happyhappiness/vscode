(strcmp(val, "block") == 0) {
					archive_entry_set_filetype(entry, AE_IFBLK);
					break;
				}