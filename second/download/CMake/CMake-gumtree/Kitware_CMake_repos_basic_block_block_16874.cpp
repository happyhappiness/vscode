{
				archive_string_copy(&(mtree->cur_dirstr),
				    &(dent->parentdir));
				archive_strappend_char(
				    &(mtree->cur_dirstr), '/');
			}