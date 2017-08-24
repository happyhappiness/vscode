{
			if (archive_strlen(&(dent->parentdir)) > 0) {
				archive_string_copy(&(mtree->cur_dirstr),
				    &(dent->parentdir));
				archive_strappend_char(
				    &(mtree->cur_dirstr), '/');
			}
			archive_string_concat(&(mtree->cur_dirstr),
			    &(dent->basename));
		}