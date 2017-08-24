{
				archive_string_copy(&(xar->cur_dirstr),
				    &(dent->parentdir));
				archive_strappend_char(&(xar->cur_dirstr), '/');
			}