(zip_entry->system == 0) {
			// Interpret MSDOS directory bit
			if (0x10 == (external_attributes & 0x10)) {
				zip_entry->mode = AE_IFDIR | 0775;
			} else {
				zip_entry->mode = AE_IFREG | 0664;
			}
			if (0x01 == (external_attributes & 0x01)) {
				// Read-only bit; strip write permissions
				zip_entry->mode &= 0555;
			}
		}