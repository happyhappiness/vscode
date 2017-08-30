			|| (zip->hctx_valid

			 && zip->entry->aes_extra.vendor == AES_VENDOR_AE_2))) {

			if (zip->entry->flags & LA_USED_ZIP64) {

				zip->entry->crc32 = archive_le32dec(p + 4);

				zip->entry->compressed_size =

					archive_le64dec(p + 8);

				zip->entry->uncompressed_size =

					archive_le64dec(p + 16);

				zip->unconsumed = 24;

			} else {

				zip->entry->crc32 = archive_le32dec(p + 4);

