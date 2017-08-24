{
				/* Vendor version. */
				zip_entry->aes_extra.vendor =
				    archive_le16dec(p + offset);
				/* AES encryption strength. */
				zip_entry->aes_extra.strength = p[offset + 4];
				/* Actual compression method. */
				zip_entry->aes_extra.compression =
				    p[offset + 5];
			}