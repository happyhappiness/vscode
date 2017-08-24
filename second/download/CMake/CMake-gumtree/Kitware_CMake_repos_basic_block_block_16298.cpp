{
			if (archive_strlen(&(dent->file->parentdir)) > 0) {
				archive_string_copy(&(iso9660->cur_dirstr),
				    &(dent->file->parentdir));
				archive_strappend_char(&(iso9660->cur_dirstr), '/');
			}
			archive_string_concat(&(iso9660->cur_dirstr),
			    &(dent->file->basename));
		}