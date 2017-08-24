{
				archive_string_copy(&(iso9660->cur_dirstr),
				    &(dent->file->parentdir));
				archive_strappend_char(&(iso9660->cur_dirstr), '/');
			}