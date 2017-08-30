			/* Zip64 extended information extra field. */

			zip_entry->flags |= LA_USED_ZIP64;

			if (zip_entry->uncompressed_size == 0xffffffff) {

				if (datasize < 8)

					break;

				zip_entry->uncompressed_size =

				    archive_le64dec(p + offset);

				offset += 8;

				datasize -= 8;

			}

			if (zip_entry->compressed_size == 0xffffffff) {

				if (datasize < 8)

					break;

				zip_entry->compressed_size =

				    archive_le64dec(p + offset);

				offset += 8;

				datasize -= 8;

			}

			if (zip_entry->local_header_offset == 0xffffffff) {

				if (datasize < 8)

					break;

				zip_entry->local_header_offset =

				    archive_le64dec(p + offset);

				offset += 8;

				datasize -= 8;

			}

