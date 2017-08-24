(archive_entry_filetype(file->entry) == AE_IFLNK ||
		    file->content.size == 0) {
			/*
			 * Do not point a valid location.
			 * Make sure entry is not hardlink file.
			 */
			file->content.location = (*symlocation)--;
			continue;
		}