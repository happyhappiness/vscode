(0x10 == (external_attributes & 0x10)) {
				zip_entry->mode = AE_IFDIR | 0775;
			} else {
				zip_entry->mode = AE_IFREG | 0664;
			}