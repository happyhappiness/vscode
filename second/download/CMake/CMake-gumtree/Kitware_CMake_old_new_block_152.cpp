{
				zip->entry->crc32 = archive_le32dec(p + 4);
				zip->entry->compressed_size =
					archive_le64dec(p + 8);
				zip->entry->uncompressed_size =
					archive_le64dec(p + 16);
				zip->unconsumed = 24;
			}