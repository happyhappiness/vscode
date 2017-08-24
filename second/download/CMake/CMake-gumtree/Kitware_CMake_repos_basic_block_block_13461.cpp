(0x01 == (external_attributes & 0x01)) {
						// Read-only bit; strip write permissions
						zip_entry->mode &= 0555;
					}