{
				/* 4 byte "external file attributes" */
				uint32_t external_attributes;
				if (datasize < 4)
					break;
				external_attributes
				    = archive_le32dec(p + offset);
				if (zip_entry->system == 3) {
					zip_entry->mode
					    = external_attributes >> 16;
				} else if (zip_entry->system == 0) {
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
				} else {
					zip_entry->mode = 0;
				}
				offset += 4;
				datasize -= 4;
			}