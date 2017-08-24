{
				// Read-only bit; strip write permissions
				zip_entry->mode &= 0555;
			}