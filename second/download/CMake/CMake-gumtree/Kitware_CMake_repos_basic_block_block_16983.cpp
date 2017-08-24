(hardlink != NULL)
					archive_entry_set_hardlink(entry_main,
					    "././@LongHardLink");
				else
					archive_entry_set_symlink(entry_main,
					    "././@LongSymLink")