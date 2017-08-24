(xar->file->parent != NULL) {
			archive_string_concat(&(xar->file->pathname),
			    &(xar->file->parent->pathname));
			archive_strappend_char(&(xar->file->pathname), '/');
		}