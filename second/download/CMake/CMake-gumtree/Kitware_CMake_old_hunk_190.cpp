			zip->unconsumed = 4;

		}

		if (zip->entry->flags & LA_USED_ZIP64) {

			zip->entry->crc32 = archive_le32dec(p);

			zip->entry->compressed_size = archive_le64dec(p + 4);

			zip->entry->uncompressed_size = archive_le64dec(p + 12);

			zip->unconsumed += 20;

		} else {

			zip->entry->crc32 = archive_le32dec(p);

